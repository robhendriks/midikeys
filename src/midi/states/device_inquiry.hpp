#pragma once

#include "../midi_state.hpp"

namespace midikeys::states
{
    class device_inquiry : public midikeys::midi_state
    {
    public:
        device_inquiry();

        void enter(const midikeys::midi_device& device) override;

        void handle_message(const midikeys::midi_device& device, const midikeys::midi_message& message) override;

        void leave(const midikeys::midi_device& device) override;
    };
}