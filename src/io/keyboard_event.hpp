#pragma once

#include <stdint.h>

namespace midikeys
{
    enum class keyboard_code : uint8_t
    {
        arrow_up,
        arrow_down,
        arrow_left,
        arrow_right
    };

    enum class keyboard_modifiers : uint8_t
    {
        shift   = 0b00000001,
        alt     = 0b00000010,
        control = 0b00000100
    };

    struct keyboard_event
    {
        keyboard_code code;
        keyboard_modifiers modifiers;
    };
}