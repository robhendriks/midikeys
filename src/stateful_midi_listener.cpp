#include "stateful_midi_listener.hpp"
#include "midi/states/device_inquiry.hpp"
#include "midi/states/select_layout.hpp"

namespace midikeys
{
    stateful_midi_listener::stateful_midi_listener(input_manager& input_manager)
        : m_state_machine(input_manager)
    {
    }

    void stateful_midi_listener::handle_open(const midi_device& device)
    {
        m_state_machine.set_state<states::device_inquiry>(device);
    }

    void stateful_midi_listener::handle_close(const midi_device& device)
    {
        m_state_machine.set_state<states::select_layout>(device, 0, nullptr);
    }

    void stateful_midi_listener::handle_message(const midi_device& device, const midi_message& message)
    {
        m_state_machine.handle_message(device, message);
    }
}