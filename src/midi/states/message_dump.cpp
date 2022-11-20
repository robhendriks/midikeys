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
            spdlog::info("[CC] channel={}, control={}, value={}", message.channel(), message.at(1), message.at(2));
        }
        else
        {
            spdlog::warn("Unknown message type");
        }
    }

    void message_dump::leave(const midikeys::midi_device& device)
    {
    }
}