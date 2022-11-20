#include <spdlog/spdlog.h>
#include <iostream>
#include "input_manager.hpp"
#include "input_factory.hpp"
#include "midi_factory.hpp"

static int getChannel(const uint8_t statusByte) {
    if ((statusByte & 0xF0) != 0xF0)
    {
        return (statusByte & 0xF) + 1;
    }

    return 0;
}

void handleMessage(double deltatime, std::vector< unsigned char >* message, void* userData)
{
    //lpx::InputManager* im = static_cast<lpx::InputManager*>(userData);

    const size_t nBytes = message->size();

    if (nBytes > 0) {
        const uint8_t statusByte = message->at(0);

        if (statusByte >= 176 && statusByte <= 191) {
            const uint8_t channel = getChannel(statusByte);
            const uint8_t control = message->at(1);
            const uint8_t value = message->at(2);

            // Handle MIDI CC
        }
        else if (statusByte == 144) {
            const uint8_t control = message->at(1);
            const uint8_t value = message->at(2);

            //im->hello();
        }
    }
}


int main(const int argc, const char* argv[])
{
#ifndef NDEBUG
    spdlog::set_level(spdlog::level::debug);
#endif

    try {
        midikeys::midi_device midi{
            midikeys::midi_factory::make_input_default(1),
            midikeys::midi_factory::make_output_default(1)
        };

        midi.open();

        midikeys::input_manager input{
           midikeys::input_factory::make_platform_default()
        };

        input.initialize();

        char c;
        std::cin.get(c);
    }
    catch (const std::exception& e) {
        spdlog::error("Unable to initialize: {}", e.what());
        return 1;
    }

    /*lpx::InputManager im;

    im.bind(13, {});
    im.bind(14, {});
    im.bind(15, {});
    im.bind(16, {});*/

    /*RtMidiIn in;
    RtMidiOut out;

    in.ignoreTypes(false, true, true);

    const size_t nPorts = in.getPortCount();
    const size_t port = nPorts - 1;

    spdlog::info("Port count: {} {}", nPorts, in.getPortName(port));

    out.openPort(port);

    in.setCallback(&handleMessage, &im);
    in.openPort(port);

    if (!out.isPortOpen() || !in.isPortOpen()) {
        spdlog::error("Unable to open MIDI port {}", port);
        return 1;
    }

    std::vector<uint8_t> sysExOpen{ 240, 0, 32, 41, 2, 12, 14, 1, 247 };
    out.sendMessage(&sysExOpen);

    std::vector<uint8_t> sysExVelocity{ 240, 0, 32, 41, 2, 12, 4, 0, 247 };
    out.sendMessage(&sysExVelocity);

    char input;
    std::cin.get(input);

    std::vector<uint8_t> sysExClose{ 240, 0, 32, 41, 2, 12, 14, 0, 247 };
    out.sendMessage(&sysExClose);

    in.closePort();
    out.closePort();*/

    return 0;
};