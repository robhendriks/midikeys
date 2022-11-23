#include "input_api.hpp"

namespace midikeys
{
    input_api::input_api(std::unique_ptr<keyboard_handler> keyboard)
        : m_keyboard(std::move(keyboard))
    {
    }

    keyboard_handler* input_api::keyboard() const
    {
        return m_keyboard.get();
    }
}
