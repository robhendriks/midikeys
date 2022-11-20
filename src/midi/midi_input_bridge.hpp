#pragma once

#include "midi_device.hpp"
#include "../io/input_manager.hpp"

namespace midikeys
{
    struct note_event
    {
        const uint8_t channel;
        const uint8_t note;
        const uint8_t velocity;
    };

    struct control_change_event
    {
        const uint8_t channel;
        const uint8_t note;
        const uint8_t velocity;
    };

    class midi_input_bridge
    {
    public:
        void handle_control_change(const input_manager& input, const midi_device& midi, const control_change_event& event) const;
    };
}