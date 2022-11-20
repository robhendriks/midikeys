#include "rtmidi_output.hpp"

namespace midikeys
{
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

    void rtmidi_output::send_message(const midi_message& message) const
    {
        if (m_out.isPortOpen()) {
            m_out.sendMessage(&message.bytes());
        }
    }

    std::string rtmidi_output::port_name() const
    {
        return m_out.getPortName(port_number());
    };
}