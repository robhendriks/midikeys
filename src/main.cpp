#include <spdlog/spdlog.h>
#include <iostream>
#include "io/input_manager.hpp"
#include "io/input_factory.hpp"
#include "midi/midi_factory.hpp"
#include "midi/midi_listener.hpp"
#include "midi/midi_device.hpp"
#include "midi/midi_state_machine.hpp"
#include "midi/states/device_inquiry.hpp"
#include "midi/states/select_layout.hpp"

class input_listener : public midikeys::midi_listener
{
    midikeys::input_manager& m_input_manager;
    midikeys::midi_state_machine m_state_machine;

public:
    input_listener(midikeys::input_manager& input_manager)
        : m_input_manager(input_manager),
        m_state_machine()
    {
    }

    void handle_open(const midikeys::midi_device& device)
    {
        m_state_machine.set_state<midikeys::states::device_inquiry>(device);
    }

    void handle_close(const midikeys::midi_device& device)
    {
        m_state_machine.set_state<midikeys::states::select_layout>(device, 0);
    }

    void handle_message(const midikeys::midi_device& device, const midikeys::midi_message& message) override
    {
        m_state_machine.handle_message(device, message);
    }
};


int main(const int argc, const char* argv[])
{
#ifndef NDEBUG
    spdlog::set_level(spdlog::level::debug);
#endif

    try {
        midikeys::input_manager input_manager{
            midikeys::input_factory::make_platform_default()
        };

        input_manager.initialize();

        midikeys::midi_device midi_device{
            midikeys::midi_factory::make_input_default(0),
            midikeys::midi_factory::make_output_default(1),
            std::make_unique<input_listener>(input_manager)
        };

        auto midi_worker = midi_device.open();

        char c;
        std::cin.get(c);

        midi_worker->dispose();
        midi_device.close();
    }
    catch (const std::exception& e) {
        spdlog::error("Unable to initialize: {}", e.what());
        return 1;
    }

    return 0;
};