#include "midi_message.hpp"
#include "midi_util.hpp"

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