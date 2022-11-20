#pragma once

#include "midi_message.hpp"

namespace midikeys::midi_util
{
    inline uint8_t make_command(const message_type type, const uint8_t channel)
    {
        return static_cast<uint8_t>(type) | (channel - 1);
    }
}