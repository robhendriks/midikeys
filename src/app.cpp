#include "app.hpp"
#include "midi/midi_api_factory.hpp"
#include "device/device_profile.hpp"
#include "input/input_api_factory.hpp"
#include <spdlog/spdlog.h>

namespace midikeys {
    app_paths app_paths::make_default()
    {
        const fs::path root = fs::current_path();

        return {
            root,
            root / "mappings",
            root / "profiles"
        };
    }

    fs::path app_paths::get_mapping_path(const std::string& name) const
    {
        return mapping_dir_path / (name + ".yml");
    }

    fs::path app_paths::get_profile_path(const std::string& name) const
    {
        return profile_dir_path / (name + ".yml");
    }

    app_options app_options::from_cmdl(const argh::parser& cmdl) {
        const bool verbose = cmdl[{"-v", "--verbose"}];
        return { verbose };
    }

    app::app(app_paths paths) noexcept
        : m_paths(std::move(paths)),
        m_midi_api(nullptr),
        m_midi_device(nullptr),
        m_device_manager(nullptr) {}

    bool app::initialize_device_manager(const argh::parser& cmdl)
    {
        const auto& pos_args = cmdl.pos_args();

        if (pos_args.size() < 3) {
            return false;
        }

        const fs::path mapping_path = m_paths.get_mapping_path(pos_args.at(1));
        const fs::path profile_path = m_paths.get_profile_path(pos_args.at(2));

        m_device_manager = std::make_unique<device_manager>(
            input_api_factory::make_platform_default());

        return m_device_manager->try_load_profile(profile_path)
            && m_device_manager->try_load_mapping(mapping_path);
    }

    bool app::initialize_midi_api(const argh::parser& cmdl) {
        m_midi_api = midi_api_factory::make_platform_default();

        const midi_port_discovery_result result = m_midi_api->discover_ports();

        size_t input_port_number;
        size_t output_port_number;

        if (!(cmdl({ "-i", "--input" }) >> input_port_number)) {
            spdlog::error("Please specify a MIDI input port number using '--input=<port_number>'");
            return false;
        }

        const auto input_port_descriptor = result.find_input(input_port_number);

        if (!input_port_descriptor.has_value()) {
            spdlog::error("Invalid MIDI input port: {}", input_port_number);
            return false;
        }

        if (!(cmdl({ "-o", "--output" }) >> output_port_number)) {
            spdlog::error("Please specify a MIDI output port number using '--output=<port_number>'");
            return false;
        }

        const auto output_port_descriptor = result.find_output(output_port_number);

        if (!output_port_descriptor.has_value()) {
            spdlog::error("Invalid MIDI output port: {}", output_port_number);
            return false;
        }

        m_midi_device = m_midi_api->make_device(
            input_port_descriptor.value(),
            output_port_descriptor.value());

        m_midi_device->set_listener(shared_from_this());

        return true;
    }

    void app::run_command_root(const argh::parser& cmdl) {
        if (!initialize_device_manager(cmdl)) {
            return;
        }

        if (!initialize_midi_api(cmdl)) {
            return;
        }

        const auto worker = m_midi_device->open();

        char c;
        std::cin.get(c);

        worker->dispose();
        m_midi_device->close();
    }

    void app::run_command_verify(const argh::parser& cmdl) {
        const auto& pos_args = cmdl.pos_args();

        initialize_device_manager(cmdl);
    }

    void app::run_command_list(const argh::parser&) {
        m_midi_api = midi_api_factory::make_platform_default();

        const midi_port_discovery_result result = m_midi_api->discover_ports();

        if (!result.inputs.empty()) {
            for (const midi_port_descriptor& input : result.inputs) {
                spdlog::info("[INPUT] {} --> '{}'", input.port_number, input.port_name);
            }
        }
        else {
            spdlog::warn("No MIDI inputs available.");
        }

        if (!result.outputs.empty()) {
            for (const midi_port_descriptor& output : result.outputs) {
                spdlog::info("[OUTPUT] {} --> '{}'", output.port_number, output.port_name);
            }
        }
        else {
            spdlog::warn("No MIDI outputs available.");
        }
    }

    void app::configure(const app_options& options) {
        if (options.verbose) {
            spdlog::set_level(spdlog::level::debug);
        }
    }

    void app::run(const char** argv) {
        const argh::parser cmdl(argv);

        const app_options options = app_options::from_cmdl(cmdl);
        configure(options);

        bool is_command_verify = cmdl[{"--verify"}];
        bool is_command_list = cmdl[{"--list"}];


        if (is_command_verify) {
            run_command_verify(cmdl);
        }
        else if (is_command_list) {
            run_command_list(cmdl);
        }
        else {
            run_command_root(cmdl);
        }
    }

    void app::handle_open(const midi_device& device)
    {
        m_device_manager->handle_open(device); // Proxy to device manager
    }

    void app::handle_message(const midi_device& device, const midi_message& message)
    {
        m_device_manager->handle_message(device, message); // Proxy to device manager
    }

    void app::handle_close(const midi_device& device)
    {
        m_device_manager->handle_close(device); // Proxy to device manager
    }
}
