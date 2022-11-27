#include "midi_port.hpp"

namespace midikeys {
    midi_port::midi_port(midi_port_descriptor descriptor)
        : m_device(nullptr), m_descriptor(std::move(descriptor)) {}

    size_t midi_port::port_number() const {
        return m_descriptor.port_number;
    }

    std::string_view midi_port::port_name() const {
        return m_descriptor.port_name;
    }

    midi_device* midi_port::device() const
    {
        return m_device;
    }

    void midi_port::set_device(midi_device* device) {
        m_device = device;
    }
}
