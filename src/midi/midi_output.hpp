#pragma once

#include "midi_port.hpp"
#include "midi_message.hpp"

namespace midikeys
{
    class midi_output : public midi_port
    {
    public:
        explicit midi_output(midi_port_descriptor descriptor);

        virtual ~midi_output() = default;

        virtual void send_message(const midi_message& message) const = 0;
    };
}