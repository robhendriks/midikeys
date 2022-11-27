#include "rtmidi_input.hpp"
#include "midi_device.hpp"
#include <spdlog/spdlog.h>

namespace midikeys {
    rtmidi_input::rtmidi_input(midi_port_descriptor descriptor)
        : midi_input(std::move(descriptor)) {}

    bool rtmidi_input::open() {
        if (m_in.isPortOpen()) {
            return true;
        }

        m_in.setErrorCallback([](RtMidiError::Type type, const std::string& error_text, void* user_data)
            {
                const rtmidi_input* in = static_cast<rtmidi_input*>(user_data);
                const midi_device* device = in->device();

                if (device->listener()) {
                    device->listener()->handle_error(*device, error_text);
                }

            }, this);

        m_in.setCallback([](double timeStamp, std::vector<unsigned char>* message, void* userData)
            {
                const auto in = static_cast<rtmidi_input*>(userData);
        in->device()->listener()->handle_message(*in->device(), {});
            }, this);

        m_in.ignoreTypes(false, true, true);
        m_in.openPort(port_number());

        return m_in.isPortOpen();
    }

    void rtmidi_input::close() {
        if (m_in.isPortOpen()) {
            m_in.closePort();
        }
    }
}
