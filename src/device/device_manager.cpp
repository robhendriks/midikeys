#include "device_manager.hpp"
#include "../midi/midi_device.hpp"
#include <stdexcept>
#include <spdlog/spdlog.h>
#include <algorithm>

namespace midikeys
{
    int device_state::make_key(const size_t channel, const size_t control)
    {
        return channel * 1000 + control;
    }

    void device_state::initialize(device_mapping& mapping)
    {
        for (auto& input : mapping.inputs) {
            const int key = device_state::make_key(input.midi_channel, input.midi_control);

            input_states[key] = std::make_tuple(&input, false);
        }
    }

    device_manager::device_manager() {}

    void device_manager::midi_update(const midi_device& device) const
    {
        for (const auto& it : m_state.input_states) {
            const bool is_pressed = std::get<1>(it.second);
            const device_input_mapping* input_mapping = std::get<0>(it.second);

            const std::string& color_name = is_pressed
                ? input_mapping->color_on
                : input_mapping->color_off;

            const auto color_it = m_profile.color_map.find(color_name);
            if (color_it == m_profile.color_map.end()) {
                continue;
            }

            const auto message = midi_message::make_control_change(
                input_mapping->midi_channel,
                input_mapping->midi_control,
                color_it->second);

            device.output().send_message(message);
        }
    }

    bool device_manager::try_load_mapping(const fs::path& path)
    {
        try {
            m_mapping = device_mapping::from_yaml_file(path);
            m_state.initialize(m_mapping);

            return true;
        }
        catch (const std::exception& e) {
            spdlog::error("Invalid mapping '{}': {}", path.string(), e.what());
            return false;
        }
    }

    bool device_manager::try_load_profile(const fs::path& path)
    {
        try {
            m_profile = device_profile::from_yaml_file(path);
            return true;
        }
        catch (const std::exception& e) {
            spdlog::error("Invalid profile '{}': {}", path.string(), e.what());
            return false;
        }
    }

    void device_manager::handle_open(const midi_device& device)
    {
        for (const auto& msg : m_profile.message_map.open) {
            device.output().send_message(static_cast<midi_message>(msg));
        }

        midi_update(device);
    }

    void device_manager::handle_message(const midi_device& device, const midi_message& message)
    {
        if (message.type() != message_type::NOTE_ON && message.type() != message_type::NOTE_OFF) {
            return;
        }

        const size_t channel = message.channel();
        const size_t control = message.at(1);
        const size_t velocity = message.at(2);

        const bool is_pressed = velocity > 0;
        const int key = device_state::make_key(channel, control);

        const auto input_state_it = m_state.input_states.find(key);

        if (input_state_it != m_state.input_states.end()) {
            device_input_mapping* input_mapping = std::get<0>(input_state_it->second);

            m_state.input_states[key] = std::make_tuple(input_mapping, is_pressed);
            midi_update(device);
        }
    }

    void device_manager::handle_close(const midi_device& device)
    {
        for (const auto& msg : m_profile.message_map.close) {
            device.output().send_message(static_cast<midi_message>(msg));
        }
    }

    const device_mapping& device_manager::mapping() const
    {
        return m_mapping;
    }

    const device_profile& device_manager::profile() const
    {
        return m_profile;
    }
}
