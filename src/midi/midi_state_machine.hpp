#pragma once

#include "midi_device.hpp"
#include "midi_message.hpp"
#include "../io/input_manager.hpp"
#include <memory>

namespace midikeys
{
    class midi_state;

    class midi_state_machine
    {
        input_manager& m_input;
        std::unique_ptr<midi_state> m_state;
    public:
        midi_state_machine(input_manager& input);

        void handle_message(const midi_device& device, const midi_message& message);

        void set_state(const midi_device& device, std::unique_ptr<midi_state> state);

        template<class Ty, class... Args>
        void set_state(const midi_device& device, Args&&... args)
        {
            set_state(device, std::make_unique<Ty>(std::forward<Args>(args)...));
        }

        input_manager& input();
        const input_manager& input() const;
    };
}