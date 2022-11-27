#pragma once

#include "midi_api.hpp"
#include <RtMidi.h>

namespace midikeys {
    class rtmidi_api : public midi_api {
        static std::vector<midi_port_descriptor> create_port_descriptors(RtMidi& port);

    public:
        midi_port_discovery_result discover_ports() const override;

        std::unique_ptr<midi_device> make_device(
            const std::string& name,
            const midikeys::midi_port_descriptor& input_port_descriptor,
            const midikeys::midi_port_descriptor& output_port_descriptor,
            midi_listener* listener) const override;

        std::string name() const override;
    };
}
