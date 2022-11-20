#pragma once

#include "../midi_state.hpp"

namespace midikeys::states
{

    class select_layout : public midi_state
    {
        std::unique_ptr<midi_state> m_next_state;
        const uint8_t m_layout_id;

    public:
        select_layout(const uint8_t layout_id, std::unique_ptr<midi_state> next_state);

        void enter(const midikeys::midi_device& device) override;

        void handle_message(const midikeys::midi_device& device, const midikeys::midi_message& message) override;

        void leave(const midikeys::midi_device& device) override;
    };
}