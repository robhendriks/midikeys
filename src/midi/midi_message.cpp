#include "midi_message.hpp"
#include "midi_util.hpp"
#include <algorithm>

namespace midikeys
{
    midi_message::midi_message(std::vector<uint8_t> bytes)
        : m_bytes(std::move(bytes))
    {
    }

    midi_message::midi_message(std::initializer_list<uint8_t> args)
        : m_bytes(args)
    {

    }

    midi_message::midi_message()
        : m_bytes()
    {
    }

    midi_message midi_message::control_change(const uint8_t channel, const uint8_t control, const uint8_t value)
    {
        return{ midi_util::make_command(message_type::CONTROL_CHANGE, channel), control, value };
    }

    midi_message midi_message::note_off(const uint8_t channel, const uint8_t note, const uint8_t velocity)
    {
        return { midi_util::make_command(message_type::NOTE_ON, channel), note, velocity };
    }

    midi_message midi_message::note_on(const uint8_t channel, const uint8_t note, const uint8_t velocity)
    {
        return { midi_util::make_command(message_type::NOTE_ON, channel), note, velocity };
    }

    message_type midi_message::type() const
    {
        if (is_empty()) {
            return message_type::NONE;
        }

        const uint8_t status_byte = first();

        if (status_byte >= 176 && status_byte <= 191) {
            return message_type::CONTROL_CHANGE;
        }
        else if (status_byte == 144) {
            return message_type::NOTE_ON;
        }
        else if (status_byte == 128) {
            return message_type::NOTE_OFF;
        }

        return message_type::NONE;
    }

    bool midi_message::is_of_type(const message_type expected_type) const
    {
        return type() == expected_type;
    }

    bool midi_message::is_empty() const
    {
        return m_bytes.empty();
    }

    bool midi_message::starts_with(const uint8_t byte) const
    {
        return !is_empty() && first() == byte;
    }

    bool midi_message::starts_with_sequence(std::initializer_list<const uint8_t> expected_bytes) const
    {
        if (expected_bytes.size() > size()) {
            return false;
        }

        size_t idx = 0;
        for (const uint8_t expected_byte : expected_bytes) {
            if (m_bytes[idx] != expected_byte) {
                return false;
            }
            idx++;
        }

        return true;
    }

    bool midi_message::ends_with(const uint8_t byte) const
    {
        return !is_empty() && last() == byte;
    }

    bool midi_message::has_size(const size_t size) const
    {
        return m_bytes.size() == size;
    }

    int midi_message::compare_byte(const size_t index, const uint8_t byte) const
    {
        return !is_empty() && at(index) == byte;
    }

    uint8_t midi_message::channel() const
    {
        const uint8_t status_byte = first();

        if ((status_byte & 0xF0) != 0xF0)
        {
            return (status_byte & 0xF) + 1;
        }

        return 0;
    }

    uint8_t midi_message::at(const size_t index) const
    {
        return m_bytes.at(index);
    }

    uint8_t midi_message::first() const
    {
        return m_bytes.front();
    }

    uint8_t midi_message::last() const
    {
        return m_bytes.back();
    }

    std::vector<uint8_t>& midi_message::bytes()
    {
        return m_bytes;
    }

    const std::vector<uint8_t>& midi_message::bytes() const
    {
        return m_bytes;
    }

    size_t midi_message::size() const
    {
        return m_bytes.size();
    }

    std::vector<uint8_t>::iterator midi_message::begin()
    {
        return m_bytes.begin();
    }

    std::vector<uint8_t>::iterator midi_message::end()
    {
        return m_bytes.end();
    }
}