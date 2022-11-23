#include "midi_device.hpp"
#include <stdexcept>
#include <spdlog/spdlog.h>

namespace midikeys
{
    midi_device::midi_device(std::unique_ptr<midi_input> input, std::unique_ptr<midi_output> output)
        : m_input(std::move(input)),
        m_output(std::move(output)),
        m_listener(std::weak_ptr<midi_listener>())
    {
    }

    std::shared_ptr<midi_worker> midi_device::open()
    {
        if (!m_input->open()) {
            throw std::runtime_error(fmt::format("Unable to open MIDI input on port {}.", m_input->port_number()));
        }

        spdlog::debug("Using MIDI input on port {} '{}'", m_input->port_number(), m_input->port_name());

        if (!m_output->open()) {
            throw std::runtime_error(fmt::format("Unable to open MIDI output on port {}.", m_output->port_number()));
        }

        spdlog::debug("Using MIDI output on port {} '{}'", m_output->port_number(), m_output->port_name());

        auto worker = std::make_shared<midi_worker>(*this);

        if (auto listener = m_listener.lock()) {
            listener->handle_open(*this);
        }
        else {
            spdlog::warn("No listener defined.");
        }

        return worker;
    }

    void midi_device::close()
    {
        spdlog::debug("Closing MIDI ports");

        if (auto listener = m_listener.lock()) {
            listener->handle_close(*this);
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

    std::weak_ptr<midi_listener> midi_device::listener() const {
        return m_listener;
    }

    void midi_device::set_listener(std::weak_ptr<midi_listener> listener) {
        m_listener = std::move(listener);
    }
}
