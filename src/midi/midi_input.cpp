#include "midi_input.hpp"

namespace midikeys {
    midi_input::midi_input(midi_port_descriptor descriptor)
        : midi_port(std::move(descriptor)) {}
}
