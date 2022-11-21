#pragma once

#include <memory>
#include "input_handler.hpp"
#include "keyboard_event.hpp"
#include "input_mapping.hpp"

namespace midikeys
{
    class input_manager
    {
        std::unique_ptr<input_handler> m_handler;
        std::unique_ptr<input_mapping> m_mapping;
    public:
        input_manager(std::unique_ptr<input_handler> handler, std::unique_ptr<input_mapping> mapping);

        void initialize();

        void send_keyboard_event(const keyboard_event& event) const;

        input_handler& handler();
        const input_handler& handler() const;

        input_mapping& mapping();
        const input_mapping& mapping() const;
    };
}