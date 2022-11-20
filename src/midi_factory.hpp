#pragma once

#include "midi_device.hpp"
#include "rtmidi_ports.hpp"

namespace midikeys::midi_factory
{
    inline std::unique_ptr<midi_input> midi_factory::make_input_default(const size_t port_number)
    {
#ifdef USE_RTMIDI_API
        return std::make_unique<rtmidi_input>(port_number);
#else
        throw std::runtime_error("Unable to determine MIDI back-end.");
#endif
    }

    inline std::unique_ptr<midi_output> midi_factory::make_output_default(const size_t port_number)
    {
#ifdef USE_RTMIDI_API
        return std::make_unique<rtmidi_output>(port_number);
#else
        throw std::runtime_error("Unable to determine MIDI back-end.");
#endif
    }
}