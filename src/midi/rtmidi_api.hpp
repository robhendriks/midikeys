#pragma once

#include "midi_api.hpp"
#include <RtMidi.h>

namespace midikeys {
    class rtmidi_api : public midi_api {
        static std::vector<midi_port_descriptor> create_port_descriptors(RtMidi &port);

    public:
        midi_port_discovery_result discover_ports() const override;
    };
}