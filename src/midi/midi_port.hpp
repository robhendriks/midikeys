#pragma once

#include <string>

namespace midikeys
{
    class midi_port
    {
        const size_t m_port_number;
    public:
        explicit midi_port(const size_t port_number);

        size_t port_number() const;

        virtual std::string port_name() const = 0;
        virtual bool open() = 0;
        virtual void close() = 0;
    };
}