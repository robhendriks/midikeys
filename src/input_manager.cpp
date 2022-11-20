#include "input_manager.hpp"
#include <spdlog/spdlog.h>

namespace midikeys
{
    input_manager::input_manager(std::unique_ptr<input_handler> handler)
        : m_handler(std::move(handler))
    {
    }

    void input_manager::initialize()
    {
        spdlog::debug("Using '{}' input handler", m_handler->platform());
    }
}