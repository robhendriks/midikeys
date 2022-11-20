#pragma once

#include "input_handler.hpp"

namespace midikeys
{
    class windows_input_handler : public input_handler
    {
        static const std::string s_platform;

    public:
        std::string_view platform() const override;
        void send_keyboard_event(const keyboard_event& event) const override;
    };
}