#include "windows_input_handler.hpp"
#include <Windows.h>
#include <spdlog/spdlog.h>

namespace midikeys
{
    const std::string windows_input_handler::s_platform = "Windows";

    int windows_input_handler::get_windows_key(const keyboard_code code)
    {
        switch (code)
        {
        case keyboard_code::arrow_up:
            return VK_UP;
        case keyboard_code::arrow_down:
            return VK_DOWN;
        case keyboard_code::arrow_left:
            return VK_LEFT;
        case keyboard_code::arrow_right:
            return VK_RIGHT;
        default:
            throw std::out_of_range("Unsupported Windows key code.");
        }
    }

    void windows_input_handler::send_keyboard_event(const keyboard_event& event) const
    {
        INPUT inputs[4] = {};
        ZeroMemory(inputs, sizeof(inputs));

        const int windows_key = get_windows_key(event.code);

        inputs[0].type = INPUT_KEYBOARD;
        inputs[0].ki.wVk = windows_key;

        inputs[1].type = INPUT_KEYBOARD;
        inputs[1].ki.wVk = windows_key;
        inputs[1].ki.dwFlags = KEYEVENTF_KEYUP;

        UINT uSent = SendInput(ARRAYSIZE(inputs), inputs, sizeof(INPUT));
        if (uSent != ARRAYSIZE(inputs))
        {
            spdlog::error("[Windows] Unable to send keyboard input: {}", HRESULT_FROM_WIN32(GetLastError()));
        }
    }

    std::string_view windows_input_handler::platform() const
    {
        return s_platform;
    }
}