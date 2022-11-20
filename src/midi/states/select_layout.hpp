#pragma once

#include "../midi_state.hpp"

namespace midikeys::states
{

    class select_layout : public midikeys::midi_state
    {
        const uint8_t m_layout_id;

    public:
        select_layout(const uint8_t layout_id);

        void enter(const midikeys::midi_device& device) override;

        void handle_message(const midikeys::midi_device& device, const midikeys::midi_message& message) override;

        void leave(const midikeys::midi_device& device) override;
    };
}