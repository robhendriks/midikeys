#pragma once

#include <memory>
#include "input_handler.hpp"

namespace midikeys
{
    class input_manager
    {
        std::unique_ptr<input_handler> m_handler;
    public:
        explicit input_manager(std::unique_ptr<input_handler> handler);

        void initialize();

        input_handler& handler();
        const input_handler& handler() const;
    };
}