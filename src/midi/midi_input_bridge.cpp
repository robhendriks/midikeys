#include "midi_input_bridge.hpp"
#include <spdlog/spdlog.h>

namespace midikeys
{
    void midi_input_bridge::handle_control_change(const input_manager& input, const midi_device& midi, const control_change_event& event) const
    {
        if (event.value < 1) {
            return;
        }

        const input_binding* binding = input.mapping().get_binding(event.channel, event.control);

        if (binding) {
            spdlog::debug("[BINDING] channel={}, control={}", event.channel, event.control);
            input.send_keyboard_event({ binding->code, binding->modifiers });
        }
    }
}