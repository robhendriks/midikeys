#pragma once

#include "midi_api.hpp"
#include <vector>

namespace midikeys
{
    class midi_device_manager
    {
        std::unique_ptr<midi_api> m_api;
    public:
        midi_device_manager();

        void initialize();
    };
}
