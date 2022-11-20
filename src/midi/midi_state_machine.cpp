#include "midi_state_machine.hpp"
#include "midi_state.hpp"
#include <spdlog/spdlog.h>

namespace midikeys
{
    midi_state_machine::midi_state_machine()
        : m_state(nullptr)
    {
    }

    void midi_state_machine::handle_message(const midi_device& device, const midi_message& message)
    {
        if (m_state) {
            m_state->handle_message(device, message);
        }
    }

    void midi_state_machine::set_state(const midi_device& device, std::unique_ptr<midi_state> state)
    {
        if (m_state) {
            spdlog::debug("[STATE_LEAVE] {}", m_state->name());
            m_state->leave(device);
            m_state->m_machine = nullptr;
        }

        if (!state) {
            spdlog::debug("[STATE_NULL]");
            m_state = nullptr;
            return;
        }

        m_state = std::move(state);
        m_state->m_machine = this;

        spdlog::debug("[STATE_ENTER] {}", m_state->name());
        m_state->enter(device);
    }
}