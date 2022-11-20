#include "select_layout.hpp"

#include <spdlog/fmt/fmt.h>

namespace midikeys::states
{
    select_layout::select_layout(const uint8_t layout_id)
        : midikeys::midi_state(fmt::format("select_layout(layout_id={})", layout_id)), m_layout_id(layout_id)
    {
    }

    void select_layout::enter(const midikeys::midi_device& device)
    {
        midikeys::midi_message message{ 240, 0, 32, 41, 2, 12, 14, 1, 247 };
        device.output().send_message(message);
    }

    void select_layout::handle_message(const midikeys::midi_device& device, const midikeys::midi_message& message)
    {
    }

    void select_layout::leave(const midikeys::midi_device& device)
    {
    }
}