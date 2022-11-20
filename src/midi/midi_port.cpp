#include "midi_port.hpp"

namespace midikeys
{
    midi_port::midi_port(const size_t port_number)
        : m_port_number(port_number)
    {
    }

    size_t midi_port::port_number() const
    {
        return m_port_number;
    }
}