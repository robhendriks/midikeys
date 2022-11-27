#pragma once

#include "midi_listener.hpp"
#include "midi_input.hpp"
#include "midi_output.hpp"
#include <memory>

namespace midikeys {

    class midi_device {
        std::string m_name;
        std::unique_ptr<midi_input> m_input;
        std::unique_ptr<midi_output> m_output;
        std::weak_ptr<midi_listener> m_listener;

    public:
        midi_device(std::string name, std::unique_ptr<midi_input> input, std::unique_ptr<midi_output> output);

        void open();

        void close();

        midi_input& input();

        const midi_input& input() const;

        midi_output& output();

        const midi_output& output() const;

        std::weak_ptr<midi_listener> listener() const;

        void set_listener(std::weak_ptr<midi_listener> listener);

        const std::string& name() const;
    };
}
