#include "midi_device.hpp"
#include <stdexcept>
#include <spdlog/spdlog.h>

namespace midikeys
{
    midi_device::midi_device(std::string name, std::unique_ptr<midi_input> input, std::unique_ptr<midi_output> output, midi_listener* listener)
        : m_name(std::move(name)),
        m_input(std::move(input)),
        m_output(std::move(output)),
        m_listener(listener)
    {
        m_input->set_device(this);
        m_output->set_device(this);
    }

    void midi_device::open()
    {
        if (!m_input->open()) {
            throw std::runtime_error(fmt::format("Unable to open MIDI input on port {}.", m_input->port_number()));
        }

        if (!m_output->open()) {
            throw std::runtime_error(fmt::format("Unable to open MIDI output on port {}.", m_output->port_number()));
        }

        if (m_listener) {
            m_listener->handle_open(*this);
        }
    }

    void midi_device::close()
    {
        if (m_listener) {
            m_listener->handle_close(*this);
        }

        m_output->close();
        m_input->close();
    }

    midi_input& midi_device::input()
    {
        return *m_input;
    }

    const midi_input& midi_device::input() const
    {
        return *m_input;
    }

    midi_output& midi_device::output()
    {
        return *m_output;
    }

    const midi_output& midi_device::output() const
    {
        return *m_output;
    }

    midi_listener* midi_device::listener() const {
        return m_listener;
    }

    const std::string& midi_device::name() const
    {
        return m_name;
    }
}
