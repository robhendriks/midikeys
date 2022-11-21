#pragma once

#include <string>
#include <stdexcept>
#include <stdint.h>
#include <unordered_map>

namespace midikeys
{
    enum class keyboard_code : uint8_t
    {
        arrow_up,
        arrow_down,
        arrow_left,
        arrow_right
    };

    inline keyboard_code key_from_string(const std::string& str)
    {
        static const std::unordered_map<std::string, keyboard_code> codes{
            {"arrow_up", keyboard_code::arrow_up},
            {"arrow_down", keyboard_code::arrow_down},
            {"arrow_left", keyboard_code::arrow_left},
            {"arrow_right", keyboard_code::arrow_right},
        };

        const auto code_it = codes.find(str);
        if (code_it != codes.end()) {
            return code_it->second;
        }

        throw std::out_of_range("Invalid key.");
    }

    enum class keyboard_modifiers : uint8_t
    {
        none    = 1 << 0,
        super   = 1 << 1,
        shift   = 1 << 2,
        alt     = 1 << 3,
        ctrl    = 1 << 4
    };

    inline keyboard_modifiers operator|(keyboard_modifiers lhs, keyboard_modifiers rhs)
    {
        return static_cast<keyboard_modifiers>(static_cast<int>(lhs) | static_cast<int>(rhs));
    }

    inline keyboard_modifiers make_modifier(bool super, bool ctrl, bool alt, bool shift)
    {
        keyboard_modifiers modifiers = keyboard_modifiers::none;

        if (super) {
            modifiers = modifiers | keyboard_modifiers::super;
        }

        if (ctrl) {
            modifiers = modifiers | keyboard_modifiers::ctrl;
        }

        if (alt) {
            modifiers = modifiers | keyboard_modifiers::alt;
        }

        if (shift) {
            modifiers = modifiers | keyboard_modifiers::shift;
        }

        return modifiers;
    }

    struct keyboard_event
    {
        keyboard_code code;
        keyboard_modifiers modifiers;
    };
}