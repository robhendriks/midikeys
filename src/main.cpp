#include <spdlog/spdlog.h>
#include <iostream>
#include "io/input_manager.hpp"
#include "io/input_factory.hpp"
#include "midi/midi_factory.hpp"
#include "midi/midi_listener.hpp"
#include "midi/midi_device.hpp"

class input_listener : public midikeys::midi_listener
{
    midikeys::input_manager& m_input_manager;
public:
    input_listener(midikeys::input_manager& input_manager)
        : m_input_manager(input_manager)
    {
    }

    void handle_open(const midikeys::midi_device& device)
    {
        spdlog::info("[LaunchpadX] Switching into Programmer mode");

        midikeys::midi_message message{ 240, 0, 32, 41, 2, 12, 14, 1, 247 };
        device.output().send_message(message);
    }

    void handle_close(const midikeys::midi_device& device)
    {
        spdlog::info("[LaunchpadX] Switching into Live mode");

        midikeys::midi_message message{ 240, 0, 32, 41, 2, 12, 14, 0, 247 };
        device.output().send_message(message);
    }

    void handle_message(const midikeys::midi_message& message) override
    {
        spdlog::info("Message with {} byte(s)", message.size());
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
            midikeys::midi_factory::make_input_default(1),
            midikeys::midi_factory::make_output_default(1),
            std::make_unique<input_listener>(input_manager)
        };

        auto midi_worker = midi_device.open();

        char c;
        std::cin.get(c);

        midi_worker.dispose();
        midi_device.close();
    }
    catch (const std::exception& e) {
        spdlog::error("Unable to initialize: {}", e.what());
        return 1;
    }

    return 0;
};