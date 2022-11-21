#pragma once

#include "keyboard_event.hpp"

namespace midikeys
{
    struct input_binding
    {
        keyboard_code code;
        keyboard_modifiers modifiers;
    };
}