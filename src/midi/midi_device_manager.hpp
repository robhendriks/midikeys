#pragma once

#include "midi_api.hpp"
#include "../config/configuration.hpp"
#include <vector>
#include <memory>

namespace midikeys
{
    class midi_device_manager : public midi_listener
    {
        std::unique_ptr<midi_api> m_api;
        std::vector<std::unique_ptr<midi_device>> m_devices;
    public:
        midi_device_manager();

        void create_api();

        void create_devices(const std::vector<device_configuration>& device_cfgs);

        void open_device_connections();

        void close_device_connections();

        void handle_open(const midi_device& device) override;

        void handle_close(const midi_device& device) override;

        void handle_message(const midikeys::midi_device& device, const midi_message& message) override;

        void handle_error(const midi_device& device, const std::string& error_message) override;
    };
}
