#include "midi_device_manager.hpp"
#include "midi_api_factory.hpp"

#include <stdexcept>
#include <spdlog/spdlog.h>

namespace midikeys
{
    midi_device_manager::midi_device_manager()
        : m_api(nullptr), m_devices()
    {
    }

    void midi_device_manager::create_api()
    {
        if (m_api) {
            throw std::runtime_error("MIDI API already initialized.");
        }

        m_api = midi_api_factory::make_platform_default();

        spdlog::debug("Using MIDI API '{}'", m_api->name());
    }

    void midi_device_manager::create_devices(const std::vector<device_configuration>& device_cfgs)
    {
        if (!m_api) {
            throw std::runtime_error("MIDI API not yet initialized");
        }

        const auto& ports = m_api->discover_ports();

        for (const auto& device_cfg : device_cfgs) {
            const auto input_port = ports.find_input(device_cfg.input);
            const auto output_port = ports.find_output(device_cfg.output);

            if (!input_port.has_value()) {
                throw std::runtime_error("Boom boom boom.");
            }

            if (!output_port.has_value()) {
                throw std::runtime_error("Everybody say: wehooo wehoo");
            }

            m_devices.push_back(
                m_api->make_device(
                    input_port.value(),
                    output_port.value()));
        }
    }
}
