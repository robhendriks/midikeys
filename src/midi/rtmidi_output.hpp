#pragma once

#include <RtMidi.h>
#include "midi_output.hpp"

namespace midikeys
{
    class rtmidi_output : public midi_output
    {
        mutable RtMidiOut m_out;
    public:
        explicit rtmidi_output(const size_t port_number);

        bool open() override;

        void close() override;

        void send_message(const midi_message& message) const override;

        std::string port_name() const override;
    };
}