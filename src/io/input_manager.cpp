#include "input_manager.hpp"
#include <spdlog/spdlog.h>

namespace midikeys
{
    input_manager::input_manager(std::unique_ptr<input_handler> handler, std::unique_ptr<input_mapping> mapping)
        : m_handler(std::move(handler)), m_mapping(std::move(mapping))
    {
    }

    void input_manager::initialize()
    {
        spdlog::debug("Using '{}' input handler", m_handler->platform());
    }

    void input_manager::send_keyboard_event(const keyboard_event& event) const
    {
        if (m_handler) {
            m_handler->send_keyboard_event(event);
        }
    }

    input_handler& input_manager::handler()
    {
        return *m_handler;
    }

    const input_handler& input_manager::handler() const
    {
        return *m_handler;
    }

    input_mapping& input_manager::mapping()
    {
        return *m_mapping;
    }

    const input_mapping& input_manager::mapping() const
    {
        return *m_mapping;
    }
}