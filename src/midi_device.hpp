#pragma once

#include <RtMidi.h>
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

    class midi_input : public midi_port
    {
    public:
        explicit midi_input(const size_t port_number);
    };

    class midi_output : public midi_port
    {
    public:
        explicit midi_output(const size_t port_number);
    };

    namespace midi_factory
    {
        inline std::unique_ptr<midi_input> make_input_default(const size_t port_number);
        inline std::unique_ptr<midi_output> make_output_default(const size_t port_number);
    }

    class midi_device
    {
        std::unique_ptr<midi_input> m_input;
        std::unique_ptr<midi_output> m_output;

    public:
        midi_device(std::unique_ptr<midi_input> input, std::unique_ptr<midi_output> output);

        void open();
        void close();

        midi_input& input();
        midi_output& output();
    };
}