#pragma once

#include <string>

namespace midikeys {
    struct midi_port_descriptor {
        const size_t port_number;
        const std::string port_name;
    };

    class midi_port {
        const midi_port_descriptor m_descriptor;
    public:
        explicit midi_port(midi_port_descriptor descriptor);

        virtual ~midi_port() = default;

        [[nodiscard]] size_t port_number() const;

        [[nodiscard]] std::string_view port_name() const;

        virtual bool open() = 0;

        virtual void close() = 0;
    };
}