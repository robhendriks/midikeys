#pragma once

#include <RtMidi.h>
#include "midi_output.hpp"

namespace midikeys {
    class rtmidi_output : public midi_output {
        mutable RtMidiOut m_out;
    public:
        rtmidi_output(midi_port_descriptor descriptor);

        bool open() override;

        void close() override;

        void send_message(const midi_message& message) const override;
    };
}
