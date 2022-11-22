#include "midi_worker.hpp"
#include "midi_device.hpp"
#include "midi_message.hpp"
#include <spdlog/spdlog.h>
#include <vector>

namespace midikeys
{
    midi_worker::midi_worker(std::reference_wrapper<midi_device> device)
        : m_device(device), 
        m_thread(std::thread(&midi_worker::do_work, this))
    {
        spdlog::debug("Created MIDI worker thread");
    }

    midi_worker::~midi_worker()
    {
        dispose();
    }

    void midi_worker::do_work()
    {
        spdlog::debug("Started listening to incoming MIDI messages");

        m_working = true;

        midi_message message;

        while (m_working) {
            m_device.get().input().get_message(message);

            if (message.size() > 0) {
                const auto& listener = m_device.get().listener();

                if (listener) {
                    listener->handle_message(m_device.get(), message);
                }
            }
        }

        spdlog::debug("Stopped listening to incoming MIDI messages");
    }

    void midi_worker::dispose()
    {        
        if (m_thread.joinable())
        {
            spdlog::debug("Disposing worker...");

            m_working = false;
            m_thread.join();
        }
    }
}