#pragma once

#include "midi_input.hpp"
#include "midi_output.hpp"
#include "rtmidi_input.hpp"
#include "rtmidi_output.hpp"

namespace midikeys::midi_factory
{
    inline std::unique_ptr<midi_input> make_input_default(const size_t port_number)
    {
#ifdef USE_RTMIDI_API
        return std::make_unique<rtmidi_input>(port_number);
#else
        throw std::runtime_error("Unable to determine MIDI back-end.");
#endif
    }

    inline std::unique_ptr<midi_output> make_output_default(const size_t port_number)
    {
#ifdef USE_RTMIDI_API
        return std::make_unique<rtmidi_output>(port_number);
#else
        throw std::runtime_error("Unable to determine MIDI back-end.");
#endif
    }
}