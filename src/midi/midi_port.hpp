#pragma once

#include <string>

namespace midikeys {
    struct midi_port_descriptor {
        const size_t port_number;
        const std::string port_name;
    };

    class midi_device;

    class midi_port {
        friend class midi_device;

        midi_device* m_device;
        const midi_port_descriptor m_descriptor;
    protected:
        void set_device(midi_device* device);

    public:
        explicit midi_port(midi_port_descriptor descriptor);

        virtual ~midi_port() = default;

        virtual bool open() = 0;

        virtual void close() = 0;

        [[nodiscard]] size_t port_number() const;

        [[nodiscard]] std::string_view port_name() const;

        midi_device* device() const;
    };
}
