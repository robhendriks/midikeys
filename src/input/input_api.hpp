#pragma once

#include "keyboard_handler.hpp"
#include <memory>

namespace midikeys
{
    class input_api
    {
        std::unique_ptr<keyboard_handler> m_keyboard;
    public:
        input_api(std::unique_ptr<keyboard_handler> keyboard);

        virtual ~input_api() = default;

        keyboard_handler* keyboard() const;
    };
}
