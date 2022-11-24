#pragma once

#ifdef __APPLE__

#include "../input_api.hpp"
#include "../keyboard_handler.hpp"
#include <ApplicationServices/ApplicationServices.h>
#include <Carbon/Carbon.h>

namespace midikeys
{
    class apple_keyboard_press
    {
        void key_down()
        {

        }

        void key_up()
        {

        }

    public:
        apple_keyboard_press()
        {
        }

        void dispose()
        {

        }
    };


    class apple_keyboard_handler : public keyboard_handler
    {
    public:
        // static WORD get_virtual_key(const key_type type)
        // {
        // 	static std::unordered_map<key_type, WORD> map{
        // 		{ key_type::NONE, 0x00 },
        // 		{ key_type::ESCAPE, VK_ESCAPE },
        // 		{ key_type::SUPER, VK_LWIN },
        // 		{ key_type::SHIFT, VK_SHIFT },
        // 		{ key_type::CONTROL, VK_CONTROL },
        // 		{ key_type::MENU, VK_MENU },
        // 		{ key_type::F1, VK_F1 },
        // 		{ key_type::F2, VK_F2 },
        // 		{ key_type::F3, VK_F3 },
        // 		{ key_type::F4, VK_F4 },
        // 		{ key_type::F5, VK_F5 },
        // 		{ key_type::F6, VK_F6 },
        // 		{ key_type::F7, VK_F7 },
        // 		{ key_type::F8, VK_F8 },
        // 		{ key_type::F9, VK_F9 },
        // 		{ key_type::F10, VK_F10 },
        // 		{ key_type::F11, VK_F11 },
        // 		{ key_type::F12, VK_F12 },
        // 		{ key_type::ARROW_LEFT, VK_LEFT },
        // 		{ key_type::ARROW_RIGHT, VK_RIGHT },
        // 		{ key_type::ARROW_UP, VK_UP },
        // 		{ key_type::ARROW_DOWN, VK_DOWN },
        // 		{ key_type::ALPHA_A, 0x41 },
        // 		{ key_type::ALPHA_B, 0x42 },
        // 		{ key_type::ALPHA_C, 0x43 },
        // 		{ key_type::ALPHA_D, 0x44 },
        // 		{ key_type::ALPHA_E, 0x45 },
        // 		{ key_type::ALPHA_F, 0x46 },
        // 		{ key_type::ALPHA_G, 0x47 },
        // 		{ key_type::ALPHA_H, 0x48 },
        // 		{ key_type::ALPHA_I, 0x49 },
        // 		{ key_type::ALPHA_J, 0x4A },
        // 		{ key_type::ALPHA_K, 0x4B },
        // 		{ key_type::ALPHA_L, 0x4C },
        // 		{ key_type::ALPHA_M, 0x4D },
        // 		{ key_type::ALPHA_N, 0x4E },
        // 		{ key_type::ALPHA_O, 0x4F },
        // 		{ key_type::ALPHA_P, 0x50 },
        // 		{ key_type::ALPHA_Q, 0x51 },
        // 		{ key_type::ALPHA_R, 0x52 },
        // 		{ key_type::ALPHA_S, 0x53 },
        // 		{ key_type::ALPHA_T, 0x54 },
        // 		{ key_type::ALPHA_U, 0x55 },
        // 		{ key_type::ALPHA_V, 0x56 },
        // 		{ key_type::ALPHA_W, 0x57 },
        // 		{ key_type::ALPHA_X, 0x58 },
        // 		{ key_type::ALPHA_Y, 0x59 },
        // 		{ key_type::ALPHA_Z, 0x5A },
        // 		{ key_type::NUMERIC_0, 0x30 },
        // 		{ key_type::NUMERIC_1, 0x31 },
        // 		{ key_type::NUMERIC_2, 0x32 },
        // 		{ key_type::NUMERIC_3, 0x33 },
        // 		{ key_type::NUMERIC_4, 0x34 },
        // 		{ key_type::NUMERIC_5, 0x35 },
        // 		{ key_type::NUMERIC_6, 0x36 },
        // 		{ key_type::NUMERIC_7, 0x37 },
        // 		{ key_type::NUMERIC_8, 0x38 },
        // 		{ key_type::NUMERIC_9, 0x39 }
        // 	};

        // 	const auto it = map.find(type);
        // 	if (it == map.end()) {
        // 		return 0x00;
        // 	}

        // 	return it->second;
        // }

        void flush() override
        {
            std::queue<key_type>& keys = this->keys();
            if (keys.empty()) {
                return;
            }

            std::vector<apple_keyboard_press> key_presses;

            while (!keys.empty()) {
                // keys.front();

                CGKeyCode inputKeyCode = kVK_ANSI_R;

                CGEventSourceRef source = CGEventSourceCreate(kCGEventSourceStateCombinedSessionState);

                CGEventRef saveCommandDown = CGEventCreateKeyboardEvent(source, inputKeyCode, true);

                // CGEventSetFlags(saveCommandDown, kCGEventFlagMaskCommand);

                CGEventRef saveCommandUp = CGEventCreateKeyboardEvent(source, inputKeyCode, false);

                CGEventPost(kCGAnnotatedSessionEventTap, saveCommandDown);

                std::this_thread::sleep_for(std::chrono::milliseconds(10));

                CGEventPost(kCGAnnotatedSessionEventTap, saveCommandUp);

                CFRelease(saveCommandUp);
                CFRelease(saveCommandDown);
                CFRelease(source);

                keys.pop();
            }

            for (auto& key_press : key_presses) {
                key_press.dispose();
            }

            key_presses.clear();
        }
    };

    class apple_input_api : public input_api
    {
    public:
        apple_input_api()
            : input_api(std::make_unique<apple_keyboard_handler>())
        {
        }
    };
}

#endif // __APPLE__
