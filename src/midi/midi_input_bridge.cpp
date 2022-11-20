#include "midi_input_bridge.hpp"

namespace midikeys
{
    void midi_input_bridge::handle_control_change(const input_manager& input, const midi_device& midi, const control_change_event& event) const
    {
        // TODO: map midi event to keyboard code + modifier based on mapping
        //input.send_keyboard_event({ keyboard_code::arrow_left, keyboard_modifiers::shift });
    }
}