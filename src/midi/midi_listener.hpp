#pragma once

#include "midi_message.hpp"
#include <vector>

namespace midikeys {
    class midi_device;

    class midi_listener {
    public:
        virtual ~midi_listener() = default;

        virtual void handle_open(const midi_device &device) = 0;

        virtual void handle_close(const midi_device &device) = 0;

        virtual void handle_message(const midikeys::midi_device &device, const midi_message &message) = 0;
    };
}