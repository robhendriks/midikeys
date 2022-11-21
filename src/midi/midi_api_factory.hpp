#pragma once

#include "midi_api.hpp"
#include "rtmidi_api.hpp"

namespace midikeys::midi_api_factory {
    inline std::unique_ptr<midi_api> make_platform_default() {
#ifdef USE_RTMIDI_API
        return std::make_unique<rtmidi_api>();
#else
        throw std::runtime_error("Unable to determine MIDI back-end.");
#endif
    }
}