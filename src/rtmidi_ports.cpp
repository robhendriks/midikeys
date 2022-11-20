#include "rtmidi_ports.hpp"

namespace midikeys
{
    rtmidi_input::rtmidi_input(const size_t port_number)
        : midi_input(port_number)
    {
    }

    bool rtmidi_input::open()
    {
        if (m_in.isPortOpen()) {
            return true;
        }

        m_in.openPort(port_number());
        return m_in.isPortOpen();
    }

    void rtmidi_input::close()
    {
        if (m_in.isPortOpen()) {
            m_in.closePort();
        }
    }

    std::string rtmidi_input::port_name() const
    {
        return m_in.getPortName(port_number());
    };

    rtmidi_output::rtmidi_output(const size_t port_number)
        : m_out(), midi_output(port_number)
    {
    }

    bool rtmidi_output::open()
    {
        if (m_out.isPortOpen()) {
            return true;
        }

        m_out.openPort(port_number());
        return m_out.isPortOpen();
    }

    void rtmidi_output::close()
    {
        if (m_out.isPortOpen()) {
            m_out.closePort();
        }
    }

    std::string rtmidi_output::port_name() const
    {
        return m_out.getPortName(port_number());
    };
}