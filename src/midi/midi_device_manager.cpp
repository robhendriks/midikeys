#include "midi_device_manager.hpp"
#include "midi_api_factory.hpp"

#include <stdexcept>
#include <spdlog/spdlog.h>

namespace midikeys
{
    midi_device_manager::midi_device_manager()
        : m_api(nullptr)
    {
    }

    void midi_device_manager::initialize()
    {
        if (m_api) {
            throw std::runtime_error("MIDI API already initialized.");
        }

        m_api = midi_api_factory::make_platform_default();

        spdlog::debug("Using MIDI API '{}'", m_api->name());
    }
}
