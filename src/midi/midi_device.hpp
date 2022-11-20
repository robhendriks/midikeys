#pragma once

#include "midi_worker.hpp"
#include "midi_listener.hpp"
#include "midi_input.hpp"
#include "midi_output.hpp"

namespace midikeys
{
    class midi_device
    {
        std::unique_ptr<midi_input> m_input;
        std::unique_ptr<midi_output> m_output;
        std::unique_ptr<midi_listener> m_listener;

    public:
        midi_device(std::unique_ptr<midi_input> input, std::unique_ptr<midi_output> output, std::unique_ptr<midi_listener> listener);

        midi_worker open();
        void close();

        midi_input& input();
        const midi_input& input() const;
        midi_output& output();
        const midi_output& output() const;
        midi_listener& listener();
    };
}