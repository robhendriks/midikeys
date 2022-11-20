#include "windows_input_handler.hpp"
#include <Windows.h>
#include <spdlog/spdlog.h>

namespace midikeys
{
    const std::string windows_input_handler::s_platform = "Windows";

    void windows_input_handler::send_keyboard_event(const keyboard_event& event) const
    {
        INPUT inputs[4] = {};
        ZeroMemory(inputs, sizeof(inputs));

        inputs[0].type = INPUT_KEYBOARD;
        inputs[0].ki.wVk = VK_LEFT;

        inputs[1].type = INPUT_KEYBOARD;
        inputs[1].ki.wVk = VK_LEFT;
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