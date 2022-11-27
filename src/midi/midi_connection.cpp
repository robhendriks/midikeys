#include "midi_connection.hpp"
#include "midi_device.hpp"
#include "midi_message.hpp"
#include <spdlog/spdlog.h>
#include <vector>

namespace midikeys
{
    midi_connection::midi_connection(std::reference_wrapper<midi_device> device)
        : m_device(device), 
        m_thread(std::thread(&midi_connection::do_work, this))
    {
        spdlog::debug("Created MIDI worker thread");
    }

    midi_connection::~midi_connection()
    {
        dispose();
    }

    void midi_connection::do_work()
    {
        spdlog::debug("Started listening to incoming MIDI messages");

        m_working = true;

        midi_message message;

        while (m_working) {
            m_device.get().input().get_message(message);

            if (message.size() > 0) {
                const auto listener = m_device.get().listener().lock();

                if (listener) {
                    listener->handle_message(m_device.get(), message);
                }
            }

            std::this_thread::sleep_for(std::chrono::milliseconds(10));
        }

        spdlog::debug("Stopped listening to incoming MIDI messages");
    }

    void midi_connection::dispose()
    {        
        if (m_thread.joinable())
        {
            spdlog::debug("Disposing worker...");

            m_working = false;
            m_thread.join();
        }
    }
}
