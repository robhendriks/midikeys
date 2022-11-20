#include "forward_input.hpp"
#include <spdlog/spdlog.h>

namespace midikeys::states
{
    forward_input::forward_input()
        : midikeys::midi_state("forward_input"), m_bridge()
    {
    }

    void forward_input::enter(const midikeys::midi_device& device)
    {
        // TODO
    }

    void forward_input::handle_message(const midikeys::midi_device& device, const midikeys::midi_message& message)
    {
        const message_type type = message.type();

        if (type == message_type::CONTROL_CHANGE)
        {
            const uint8_t control = message.at(1);
            const uint8_t value = message.at(2);

            m_bridge.handle_control_change(machine().input(), device, { message.channel(), control, value });
        }
        if (type == message_type::NOTE_ON || type == message_type::NOTE_OFF)
        {
            const uint8_t note = message.at(1);
            const uint8_t velocity = message.at(2);

            m_bridge.handle_control_change(machine().input(), device, { message.channel(), note, velocity });
        }
    }

    void forward_input::leave(const midikeys::midi_device& device)
    {
    }
}