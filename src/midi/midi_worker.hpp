#pragma once

#include <thread>

namespace midikeys
{
    class midi_device;

    class midi_worker
    {
        friend class midi_device;

        std::reference_wrapper<midi_device> m_device;
        std::thread m_thread;
        std::atomic<bool> m_working;

    private:
        void do_work();

    public:
        explicit midi_worker(std::reference_wrapper<midi_device> device);

        midi_worker(const midi_worker&) = delete;
        midi_worker(midi_worker&&) = delete;
        ~midi_worker();

        midi_worker& operator=(const midi_worker&) = delete;
        midi_worker& operator=(midi_worker&&) = delete;

        void dispose();
    };
}