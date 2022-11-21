#pragma once

#include "midi_port.hpp"
#include "midi_message.hpp"

namespace midikeys {
    class midi_input : public midi_port {
    public:
        explicit midi_input(midi_port_descriptor descriptor);

        virtual void get_message(midi_message &message) const = 0;
    };
}