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
#include "stateful_midi_listener.hpp"

int main(const int argc, const char* argv[])
{
#ifndef NDEBUG
    spdlog::set_level(spdlog::level::debug);
#endif

    try {
        midikeys::input_manager input_manager{
            midikeys::input_factory::make_platform_default(),
            midikeys::input_mapping::from_toml_file("mappings/rekordbox.toml")
        };

        input_manager.initialize();

        midikeys::midi_device midi_device{
            midikeys::midi_factory::make_input_default(1),
            midikeys::midi_factory::make_output_default(2),
            std::make_unique<midikeys::stateful_midi_listener>(input_manager)
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