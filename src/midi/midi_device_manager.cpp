#include "midi_device_manager.hpp"
#include "midi_api_factory.hpp"
#include "../config/configuration_util.hpp"

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
                throw std::runtime_error(configuration_util::make_error_message(
                    device_cfg, "invalid MIDI in port {}", device_cfg.input));
            }

            if (!output_port.has_value()) {
                throw std::runtime_error(configuration_util::make_error_message(
                    device_cfg, "invalid MIDI out port {}", device_cfg.output));
            }

            m_devices.push_back(
                m_api->make_device(
                    device_cfg.name,
                    input_port.value(),
                    output_port.value(),
                    this));
        }
    }

    void midi_device_manager::open_device_connections()
    {
        for (const auto& device_it : m_devices) {
            device_it->open();
        }
    }

    void midi_device_manager::close_device_connections()
    {
        for (const auto& device_it : m_devices) {
            device_it->close();
        }
    }

    void midi_device_manager::handle_open(const midi_device& device)
    {
        spdlog::info("[CONN_OPEN] {}", device.name());


        //device.profile().
    }

    void midi_device_manager::handle_close(const midi_device& device)
    {
        spdlog::info("[CONN_CLOSE] {}", device.name());
    }

    void midi_device_manager::handle_message(const midikeys::midi_device& device, const midi_message& message)
    {
        spdlog::info("[MSG] {}", device.name());
    }

    void midi_device_manager::handle_error(const midi_device& device, const std::string& error_message)
    {
        spdlog::error("Error: {}", error_message);
    }
}
