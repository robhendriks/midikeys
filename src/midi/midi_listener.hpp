#pragma once

#include "midi_message.hpp"
#include <vector>
#include <string>

namespace midikeys {
    class midi_device;

    class midi_listener {
        friend class midi_device;

    public:
        virtual ~midi_listener() = default;

        virtual void handle_open(const midi_device& device) = 0;

        virtual void handle_close(const midi_device& device) = 0;

        virtual void handle_message(const midi_device& device, const midi_message& message) = 0;

        virtual void handle_error(const midi_device& device, const std::string& error_message) = 0;
    };
}
