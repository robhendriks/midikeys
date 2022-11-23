#pragma once

#include <memory>
#include "input_handler.hpp"
#include "keyboard_event.hpp"

namespace midikeys
{
    class input_manager
    {
        std::unique_ptr<input_handler> m_handler;
    public:
        input_manager(std::unique_ptr<input_handler> handler);

        void initialize();

        void send_keyboard_event(const keyboard_event& event) const;

        input_handler& handler();

        const input_handler& handler() const;
    };
}
