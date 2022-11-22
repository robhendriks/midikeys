#include "app.hpp"
#include "midi/midi_api_factory.hpp"
#include "io/input_factory.hpp"
#include "io/input_mapping.hpp"
#include "io/input_manager.hpp"
#include "device/device_profile.hpp"
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
        m_midi_device(nullptr) {}

    void app::initialize_midi_api() {
        m_midi_api = midi_api_factory::make_platform_default();
    }

    bool app::try_initialize_midi_api() {
        try {
            initialize_midi_api();
            return true;
        }
        catch (const std::exception& e) {
            spdlog::error("Unable to initialize MIDI api: {}", e.what());
            return false;
        }
    }

    void app::run_command_root(const argh::parser& cmdl) {
        if (!try_initialize_midi_api()) {
            return;
        }

        const midi_port_discovery_result result = m_midi_api->discover_ports();

        size_t input_port_number;
        size_t output_port_number;

        if (!(cmdl({ "-i", "--input" }) >> input_port_number)) {
            spdlog::error("Please specify a MIDI input port number using '--input=<port_number>'");
            return;
        }

        const auto input_port_descriptor = result.find_input(input_port_number);

        if (!input_port_descriptor.has_value()) {
            spdlog::error("Invalid MIDI input port: {}", input_port_number);
            return;
        }

        if (!(cmdl({ "-o", "--output" }) >> output_port_number)) {
            spdlog::error("Please specify a MIDI output port number using '--output=<port_number>'");
            return;
        }

        const auto output_port_descriptor = result.find_output(output_port_number);

        if (!output_port_descriptor.has_value()) {
            spdlog::error("Invalid MIDI output port: {}", output_port_number);
            return;
        }

        if (cmdl.pos_args().size() < 2) {
            spdlog::error("Usage: midikeys [options] <mapping_file>");
            return;
        }

        input_manager input{
            input_factory::make_platform_default(),
            input_mapping::from_yaml_file(cmdl.pos_args().at(1))
        };

        input.initialize();

        m_midi_device = m_midi_api->make_device(
            input_port_descriptor.value(),
            output_port_descriptor.value(),
            nullptr);

        const auto worker = m_midi_device->open();

        char c;
        std::cin.get(c);

        worker->dispose();
        m_midi_device->close();
    }

    void app::run_command_verify(const argh::parser& cmdl) {
        const auto& pos_args = cmdl.pos_args();

        if (pos_args.size() < 3) {
            spdlog::error("Usage: midikeys --verify <mapping> <profile>");
            return;
        }

        const fs::path mapping_path = m_paths.get_mapping_path(pos_args.at(1));
        if (!fs::is_regular_file(mapping_path)) {
            spdlog::error("Mapping not found: {}", mapping_path.string());
            return;
        }

        const fs::path profile_path = m_paths.get_profile_path(pos_args.at(2));
        if (!fs::is_regular_file(profile_path)) {
            spdlog::error("Profile not found: {}", profile_path.string());
            return;
        }

        try {
            const auto profile = device_profile::from_yaml_file(profile_path);
        }
        catch (const std::exception& e) {
            spdlog::error("Profile contains error(s): {}", e.what());
        }
    }

    void app::run_command_list(const argh::parser&) {
        if (!try_initialize_midi_api()) {
            return;
        }

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
}
