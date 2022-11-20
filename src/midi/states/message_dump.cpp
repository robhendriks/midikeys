#include "message_dump.hpp"
#include <spdlog/spdlog.h>

namespace midikeys::states
{
    message_dump::message_dump()
        : midikeys::midi_state("message_dump")
    {
    }

    void message_dump::enter(const midikeys::midi_device& device)
    {
    }

    void message_dump::handle_message(const midikeys::midi_device& device, const midikeys::midi_message& message)
    {
        const message_type type = message.type();

        if (type == message_type::CONTROL_CHANGE)
        {
            const uint8_t control = message.at(1);
            const uint8_t value = message.at(2);

            spdlog::info("[CC] channel={}, control={}, value={}", message.channel(), control, value);
        }
        if (type == message_type::NOTE_ON) 
        {
            const uint8_t note = message.at(1);
            const uint8_t velocity= message.at(2);

            spdlog::info("[NOTE_ON] channel={}, note={}, velocity={}", message.channel(), note, velocity);

            if (note == 11) {
                machine().input().send_keyboard_event({ keyboard_code::arrow_left });
            }
        }
        else if (type == message_type::NOTE_OFF)
        {
            spdlog::info("[NOTE_OFF] channel={}, note={}, velocity={}", message.channel(), message.at(1), message.at(2));
        }
    }

    void message_dump::leave(const midikeys::midi_device& device)
    {
    }
}