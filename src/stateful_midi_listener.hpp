#pragma once

#include "io/input_manager.hpp"
#include "midi/midi_listener.hpp"
#include "midi/midi_state_machine.hpp"

namespace midikeys
{
    class stateful_midi_listener : public midi_listener
    {
        midi_state_machine m_state_machine;

    public:
        stateful_midi_listener(input_manager& input_manager);

        void handle_open(const midi_device& device) override;

        void handle_close(const midi_device& device) override;

        void handle_message(const midi_device& device, const midi_message& message) override;
    };
}