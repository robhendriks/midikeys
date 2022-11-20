#pragma once

#include "keyboard_event.hpp"
#include <memory>
#include <string>
#include <string_view>

namespace midikeys
{
    class input_handler
    {
    public:
        virtual void send_keyboard_event(const keyboard_event& event) const = 0;
        virtual std::string_view platform() const = 0;
    };
}
