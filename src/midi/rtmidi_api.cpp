#include "rtmidi_api.hpp"
#include <RtMidi.h>

namespace midikeys {
    std::vector<midi_port_descriptor> rtmidi_api::create_port_descriptors(RtMidi &port) {
        std::vector<midi_port_descriptor> port_descriptors;

        const size_t n_ports = port.getPortCount();

        for (size_t i = 0; i < n_ports; i++) {
            port_descriptors.emplace_back(i, port.getPortName(i));
        }

        return port_descriptors;
    }

    midi_port_discovery_result rtmidi_api::discover_ports() const {
        RtMidiIn in;
        RtMidiOut out;

        return {
                create_port_descriptors(in),
                create_port_descriptors(out)
        };
    }
}