#pragma once

#include <vector>

namespace midikeys
{
    enum class message_type
    {
        NONE = 0x0,

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

        static midi_message make_control_change(const uint8_t channel, const uint8_t control, const uint8_t value);
        static midi_message make_note_off(const uint8_t channel, const uint8_t note, const uint8_t velocity);
        static midi_message make_note_on(const uint8_t channel, const uint8_t note, const uint8_t velocity);

        message_type type() const;
        bool is_of_type(const message_type expected_type) const;
        bool is_empty() const;
        bool starts_with(const uint8_t byte) const;
        bool starts_with_sequence(std::initializer_list<const uint8_t> expected_bytes) const;
        bool ends_with(const uint8_t byte) const;
        bool has_size(const size_t size) const;
        int compare_byte(const size_t index, const uint8_t byte) const;

        uint8_t channel() const;
        uint8_t at(const size_t index) const;
        uint8_t first() const;
        uint8_t last() const;

        std::vector<uint8_t>& bytes();
        const std::vector<uint8_t>& bytes() const;

        std::vector<uint8_t>::iterator begin();
        std::vector<uint8_t>::iterator end();

        size_t size() const;
    };
}
