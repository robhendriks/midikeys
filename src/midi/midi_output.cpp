#include "midi_output.hpp"

namespace midikeys {
    midi_output::midi_output(midi_port_descriptor descriptor)
        : midi_port(std::move(descriptor)) {}
}
