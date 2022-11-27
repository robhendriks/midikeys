#pragma once

#include "midi_port.hpp"
#include "midi_message.hpp"

namespace midikeys {
    class midi_input : public midi_port {
    public:
        explicit midi_input(midi_port_descriptor descriptor);

        virtual ~midi_input() = default;
    };
}
