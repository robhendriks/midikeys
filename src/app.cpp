#include "app.hpp"
#include "midi/midi_api_factory.hpp"
#include <spdlog/spdlog.h>

namespace midikeys {
    app_options app_options::from_cmdl(const argh::parser &cmdl) {
        const bool verbose = cmdl[{"-v", "--verbose"}];
        return {verbose};
    }

    app::app() noexcept: m_midi_api(nullptr) {}

    void app::initialize_midi_api() {
        m_midi_api = midi_api_factory::make_platform_default();
    }

    bool app::try_initialize_midi_api() {
        try {
            initialize_midi_api();
            return true;
        } catch (const std::exception &e) {
            spdlog::error("Unable to initialize MIDI api: {}", e.what());
            return false;
        }
    }

    void app::run_command_root(const argh::parser &cmdl) {
        if (!try_initialize_midi_api()) {
            return;
        }

        const midi_port_discovery_result result = m_midi_api->discover_ports();

        size_t input_port_number;
        size_t output_port_number;

        if (!(cmdl({"-i", "--input"}) >> input_port_number)) {
            spdlog::error("Please specify a MIDI input port number using '--input=<port_number>'");
            return;
        }

        const auto input_port_descriptor = result.find_input(input_port_number);

        if (!input_port_descriptor.has_value()) {
            spdlog::error("Invalid MIDI input port: {}", input_port_number);
            return;
        }

        if (!(cmdl({"-o", "--output"}) >> output_port_number)) {
            spdlog::error("Please specify a MIDI output port number using '--output=<port_number>'");
            return;
        }

        const auto output_port_descriptor = result.find_output(output_port_number);

        if (!output_port_descriptor.has_value()) {
            spdlog::error("Invalid MIDI output port: {}", output_port_number);
            return;
        }

        spdlog::info("MIDI ports: '{}' '{}'",
                     input_port_descriptor.value().port_name,
                     output_port_descriptor.value().port_name);

        // TODO: implement
    }

    void app::run_command_list(const argh::parser &) {
        if (!try_initialize_midi_api()) {
            return;
        }

        const midi_port_discovery_result result = m_midi_api->discover_ports();

        if (!result.inputs.empty()) {
            for (const midi_port_descriptor &input: result.inputs) {
                spdlog::info("[INPUT] {} --> '{}'", input.port_number, input.port_name);
            }
        } else {
            spdlog::warn("No MIDI inputs available.");
        }

        if (!result.outputs.empty()) {
            for (const midi_port_descriptor &output: result.outputs) {
                spdlog::info("[OUTPUT] {} --> '{}'", output.port_number, output.port_name);
            }
        } else {
            spdlog::warn("No MIDI outputs available.");
        }
    }

    void app::configure(const app_options &options) {
        if (options.verbose) {
            spdlog::set_level(spdlog::level::debug);
        }
    }

    void app::run(const char **argv) {
        const argh::parser cmdl(argv);

        const app_options options = app_options::from_cmdl(cmdl);
        configure(options);

        bool is_command_list = cmdl[{"--list"}];

        if (is_command_list) {
            run_command_list(cmdl);
        } else {
            run_command_root(cmdl);
        }
    }
}