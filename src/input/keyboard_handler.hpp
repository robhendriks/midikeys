#pragma once

#include <vector>
#include "keyboard_event.hpp"

namespace midikeys
{
    class keyboard_handler
    {
    public:
        virtual void handle_events(const std::vector<keyboard_event>& evts) const = 0;
    };
}
