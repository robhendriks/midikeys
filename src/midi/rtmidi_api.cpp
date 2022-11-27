#include "rtmidi_api.hpp"
#include "rtmidi_input.hpp"
#include "rtmidi_output.hpp"
#include <RtMidi.h>

namespace midikeys {
    std::vector<midi_port_descriptor> rtmidi_api::create_port_descriptors(RtMidi& port) {
        std::vector<midi_port_descriptor> port_descriptors;

        const size_t n_ports = port.getPortCount();

        for (size_t i = 0; i < n_ports; i++) {
            port_descriptors.push_back({ i, port.getPortName(i) });
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

    std::unique_ptr<midi_device> rtmidi_api::make_device(
        const std::string& name,
        const midikeys::midi_port_descriptor& input_port_descriptor,
        const midikeys::midi_port_descriptor& output_port_descriptor,
        midi_listener* listener
    ) const {
        return std::make_unique<midi_device>(
            name,
            std::make_unique<rtmidi_input>(input_port_descriptor),
            std::make_unique<rtmidi_output>(output_port_descriptor),
            listener);
    }

    std::string rtmidi_api::name() const
    {
        return "RtMidi";
    }
}
