#include <spdlog/spdlog.h>
#include <iostream>
#include "io/input_manager.hpp"
#include "io/input_factory.hpp"
#include "midi/midi_factory.hpp"
#include "midi/midi_listener.hpp"
#include "midi/midi_device.hpp"
#include "midi/midi_state_machine.hpp"

class select_layout_programmer : public midikeys::midi_state
{
public:
    select_layout_programmer() : midikeys::midi_state("select_layout_programmer")
    {
    }

    void enter(const midikeys::midi_device& device) override
    {
        midikeys::midi_message message{ 240, 0, 32, 41, 2, 12, 14, 1, 247 };
        device.output().send_message(message);

        // TODO: next state
    }

    void handle_message(const midikeys::midi_device& device, const midikeys::midi_message& message) override
    {
    }

    void leave(const midikeys::midi_device& device) override
    {
    }
};

class wait_for_device_inquiry : public midikeys::midi_state
{
public:
    wait_for_device_inquiry() : midikeys::midi_state("wait_for_device_inquiry")
    {
    }

    void enter(const midikeys::midi_device& device) override
    {
        device.output().send_message({ 240, 126, 127, 6, 1, 247 });
    }

    void handle_message(const midikeys::midi_device& device, const midikeys::midi_message& message) override
    {
        if (message.starts_with(240) && message.ends_with(247)) {
            if (message.size() >= 10 && message.at(9) == 1) {
                size_t build_number = message.at(12) * 1000 + message.at(13) * 100 + message.at(14) * 10 + message.at(15);
                spdlog::info("Novation Launchpad X, firmware build {}", build_number);

                machine().set_state<select_layout_programmer>(device);
            }
        }
    }

    void leave(const midikeys::midi_device& device) override
    {
    }
};

class select_layout_live : public midikeys::midi_state
{
public:
    select_layout_live() : midikeys::midi_state("select_layout_live ")
    {
    }

    void enter(const midikeys::midi_device& device) override
    {
        midikeys::midi_message message{ 240, 0, 32, 41, 2, 12, 14, 0, 247 };
        device.output().send_message(message);
    }

    void handle_message(const midikeys::midi_device& device, const midikeys::midi_message& message) override
    {
    }

    void leave(const midikeys::midi_device& device) override
    {
    }
};

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
        m_state_machine.set_state<wait_for_device_inquiry>(device);
    }

    void handle_close(const midikeys::midi_device& device)
    {
        m_state_machine.set_state<select_layout_live>(device);
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