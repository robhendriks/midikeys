#pragma once

#include "../midi_state.hpp"
#include "../midi_input_bridge.hpp"

namespace midikeys::states
{
    class forward_input : public midikeys::midi_state
    {
        midi_input_bridge m_bridge;
    public:
        forward_input();

        void enter(const midikeys::midi_device& device) override;

        void handle_message(const midikeys::midi_device& device, const midikeys::midi_message& message) override;

        void leave(const midikeys::midi_device& device) override;
    };
}