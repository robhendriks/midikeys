#include "midi_device.hpp"
#include "rtmidi_ports.hpp"
#include <stdexcept>
#include <spdlog/spdlog.h>

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

    midi_input::midi_input(const size_t port_number)
        : midi_port(port_number)
    {
    }

    midi_output::midi_output(const size_t port_number)
        : midi_port(port_number)
    {
    }

    midi_device::midi_device(std::unique_ptr<midi_input> input, std::unique_ptr<midi_output> output)
        : m_input(std::move(input)), 
        m_output(std::move(output))
    {
    }

    void midi_device::open()
    {
        if (!m_input->open()) {
            throw std::runtime_error(fmt::format("Unable to open MIDI input on port {}.", m_input->port_number()));
        }
        
        spdlog::debug("Using MIDI input on port {} '{}'", m_input->port_number(), m_input->port_name());

        if (!m_output->open()) {
            throw std::runtime_error(fmt::format("Unable to open MIDI output on port {}.", m_output->port_number()));
        }

        spdlog::debug("Using MIDI output on port {} '{}'", m_input->port_number(), m_input->port_name());
    }

    midi_input& midi_device::input()
    {
        return *m_input;
    }

    midi_output& midi_device::output()
    {
        return *m_output;
    }
}