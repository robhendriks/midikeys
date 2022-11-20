#pragma once

#include "midi_state_machine.hpp"
#include "midi_device.hpp"
#include "midi_message.hpp"
#include <string>
#include <string_view>

namespace midikeys
{
    class midi_state
    {
        friend class midi_state_machine;

        const std::string m_name;
        midi_state_machine* m_machine;

    protected:
        midi_state(std::string name);

    public:
        virtual void enter(const midi_device& device) = 0;
        virtual void handle_message(const midi_device& device, const midi_message& message) = 0;
        virtual void leave(const midi_device& device) = 0;

        std::string_view name() const;

        midi_state_machine& machine() const;
    };
}