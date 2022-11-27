#pragma once

#include <RtMidi.h>
#include "midi_input.hpp"

namespace midikeys {
    class rtmidi_input : public midi_input {
        mutable RtMidiIn m_in;
    public:
        explicit rtmidi_input(midi_port_descriptor descriptor);

        bool open() override;

        void close() override;
    };
}
