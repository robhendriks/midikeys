#pragma once

#include <RtMidi.h>
#include "midi_device.hpp"

namespace midikeys
{
    class rtmidi_input : public midi_input
    {
        mutable RtMidiIn m_in;
    public:
        explicit rtmidi_input(const size_t port_number);

        bool open() override;
        
        void close() override;

        std::string port_name() const override;
    };

    class rtmidi_output : public midi_output
    {
        mutable RtMidiOut m_out;
    public:
        explicit rtmidi_output(const size_t port_number);

        bool open() override;
        void close() override;

        std::string port_name() const override;
    };
}