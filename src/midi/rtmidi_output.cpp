#include "rtmidi_output.hpp"
#include <spdlog/spdlog.h>

namespace midikeys {
    rtmidi_output::rtmidi_output(midi_port_descriptor descriptor)
            : m_out(), midi_output(std::move(descriptor)) {
    }

    bool rtmidi_output::open() {
        if (m_out.isPortOpen()) {
            return true;
        }

        m_out.openPort(port_number());

        return m_out.isPortOpen();
    }

    void rtmidi_output::close() {
        if (m_out.isPortOpen()) {
            m_out.closePort();
        }
    }

    void rtmidi_output::send_message(const midi_message &message) const {
        if (m_out.isPortOpen()) {
            m_out.sendMessage(&message.bytes());
        }
    }
}