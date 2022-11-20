#pragma once

#include <RtMidi.h>
#include "midi_input.hpp"

namespace midikeys
{
    class rtmidi_input : public midi_input
    {
        mutable RtMidiIn m_in;
    public:
        explicit rtmidi_input(const size_t port_number);

        bool open() override;

        void close() override;

        void get_message(midi_message& message) const override;

        std::string port_name() const override;
    };
}