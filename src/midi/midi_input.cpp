#include "midi_input.hpp"

namespace midikeys
{
    midi_input::midi_input(const size_t port_number)
        : midi_port(port_number)
    {
    }
}