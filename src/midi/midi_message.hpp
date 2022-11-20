#pragma once

#include <vector>

namespace midikeys
{
    enum class message_type
    {
        NOTE_OFF = 0x80,
        NOTE_ON = 0x90,
        CONTROL_CHANGE = 0xB0,
    };

    class midi_message
    {
        std::vector<uint8_t> m_bytes;
    public:
        explicit midi_message(std::vector<uint8_t> bytes);
        midi_message(std::initializer_list<uint8_t> args);
        midi_message();

        static midi_message control_change(const uint8_t channel, const uint8_t control, const uint8_t value);
        static midi_message note_off(const uint8_t channel, const uint8_t note, const uint8_t velocity);
        static midi_message note_on(const uint8_t channel, const uint8_t note, const uint8_t velocity);

        std::vector<uint8_t>& bytes();
        const std::vector<uint8_t>& bytes() const;

        std::vector<uint8_t>::iterator begin();
        std::vector<uint8_t>::iterator end();

        size_t size() const;
    };
}