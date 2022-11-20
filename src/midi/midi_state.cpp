#include "midi_state.hpp"
#include "midi_state_machine.hpp"
#include <stdexcept>

namespace midikeys
{
    midi_state::midi_state(std::string name) 
        : m_name(std::move(name)),
        m_machine(nullptr)
    {
    }

    std::string_view midi_state::name() const
    {
        return m_name;
    }

    midi_state_machine& midi_state::machine() const
    {
        if (!m_machine) {
            throw std::runtime_error("Unable to access state machine, this state should be disposed.");
        }

        return *m_machine;
    }
}