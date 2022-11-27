#pragma once

#include <thread>

namespace midikeys
{
    class midi_device;

    class midi_connection
    {
        friend class midi_device;

        std::reference_wrapper<midi_device> m_device;
        std::thread m_thread;
        std::atomic<bool> m_working;

    private:
        void do_work();

    public:
        explicit midi_connection(std::reference_wrapper<midi_device> device);

        midi_connection(const midi_connection&) = delete;
        midi_connection(midi_connection&&) = delete;
        ~midi_connection();

        midi_connection& operator=(const midi_connection&) = delete;
        midi_connection& operator=(midi_connection&&) = delete;

        void dispose();
    };
}
