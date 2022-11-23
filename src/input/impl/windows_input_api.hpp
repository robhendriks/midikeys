#pragma once

#include "../input_api.hpp"
#include "../keyboard_handler.hpp"
#include <spdlog/spdlog.h>
#include <Windows.h>

namespace midikeys
{
    class windows_keyboard_handler : public keyboard_handler
    {
    public:
        void handle_events(const std::vector<keyboard_event>& evts) const override
        {
            INPUT ip;

            // Set up a generic keyboard event.
            ip.type = INPUT_KEYBOARD;
            ip.ki.wScan = 0; // hardware scan code for key
            ip.ki.time = 0;
            ip.ki.dwExtraInfo = 0;

            // Press the "A" key
            ip.ki.wVk = 0x41; // virtual-key code for the "a" key
            ip.ki.dwFlags = 0; // 0 for key press
            SendInput(1, &ip, sizeof(INPUT));

            // Release the "A" key
            ip.ki.dwFlags = KEYEVENTF_KEYUP; // KEYEVENTF_KEYUP for key release
            SendInput(1, &ip, sizeof(INPUT));
        }
    };

    class windows_input_api : public input_api
    {
    public:
        windows_input_api()
            : input_api(std::make_unique<windows_keyboard_handler>())
        {
        }
    };
}
