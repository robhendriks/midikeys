#include "rtmidi_input.hpp"

namespace midikeys {
    rtmidi_input::rtmidi_input(midi_port_descriptor descriptor)
            : midi_input(std::move(descriptor)) {}

    bool rtmidi_input::open() {
        if (m_in.isPortOpen()) {
            return true;
        }

        m_in.setErrorCallback([](RtMidiError::Type type, const std::string &errorText, void *userData) {
            //
        });

        m_in.ignoreTypes(false, true, true);
        m_in.openPort(port_number());

        return m_in.isPortOpen();
    }

    void rtmidi_input::close() {
        if (m_in.isPortOpen()) {
            m_in.closePort();
        }
    }

    void rtmidi_input::get_message(midi_message &message) const {
        if (m_in.isPortOpen()) {
            m_in.getMessage(&message.bytes());
        }
    }
}