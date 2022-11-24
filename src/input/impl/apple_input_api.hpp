#pragma once

#ifdef __APPLE__

#include "../input_api.hpp"
#include "../keyboard_handler.hpp"
#include <ApplicationServices/ApplicationServices.h>
#include <Carbon/Carbon.h>
#include <unordered_map>

namespace midikeys
{
    class apple_keyboard_handler : public keyboard_handler
    {
        void key_down(CGEventSourceRef source, CGKeyCode virtual_key)
        {
            CGEventRef key_down = CGEventCreateKeyboardEvent(source, virtual_key, true);
            CGEventPost(kCGAnnotatedSessionEventTap, key_down);

            CFRelease(key_down);
        }

        void key_up(CGEventSourceRef source, CGKeyCode virtual_key)
        {
            CGEventRef key_up = CGEventCreateKeyboardEvent(source, virtual_key, false);
            CGEventPost(kCGAnnotatedSessionEventTap, key_up);

            CFRelease(key_up);
        }

    public:
        static CGKeyCode get_virtual_key(const key_type type)
        {
            static std::unordered_map<key_type, CGKeyCode> map{
                { key_type::NONE, 0x00 },
                { key_type::ESCAPE, kVK_Escape },
                { key_type::SUPER, kVK_Command },
                { key_type::SHIFT, kVK_Shift },
                { key_type::CONTROL, kVK_Control },
                { key_type::MENU, kVK_Option },
                { key_type::F1, kVK_F1 },
                { key_type::F2, kVK_F2 },
                { key_type::F3, kVK_F3 },
                { key_type::F4, kVK_F4 },
                { key_type::F5, kVK_F5 },
                { key_type::F6, kVK_F6 },
                { key_type::F7, kVK_F7 },
                { key_type::F8, kVK_F8 },
                { key_type::F9, kVK_F9 },
                { key_type::F10, kVK_F10 },
                { key_type::F11, kVK_F11 },
                { key_type::F12, kVK_F12 },
                { key_type::ARROW_LEFT, kVK_LeftArrow },
                { key_type::ARROW_RIGHT, kVK_RightArrow },
                { key_type::ARROW_UP, kVK_UpArrow},
                { key_type::ARROW_DOWN, kVK_DownArrow },
                { key_type::ALPHA_A, kVK_ANSI_A },
                { key_type::ALPHA_B, kVK_ANSI_B },
                { key_type::ALPHA_C, kVK_ANSI_C },
                { key_type::ALPHA_D, kVK_ANSI_D },
                { key_type::ALPHA_E, kVK_ANSI_E },
                { key_type::ALPHA_F, kVK_ANSI_F },
                { key_type::ALPHA_G, kVK_ANSI_G },
                { key_type::ALPHA_H, kVK_ANSI_H },
                { key_type::ALPHA_I, kVK_ANSI_I },
                { key_type::ALPHA_J, kVK_ANSI_J },
                { key_type::ALPHA_K, kVK_ANSI_K },
                { key_type::ALPHA_L, kVK_ANSI_L },
                { key_type::ALPHA_M, kVK_ANSI_M },
                { key_type::ALPHA_N, kVK_ANSI_N },
                { key_type::ALPHA_O, kVK_ANSI_O },
                { key_type::ALPHA_P, kVK_ANSI_P },
                { key_type::ALPHA_Q, kVK_ANSI_Q },
                { key_type::ALPHA_R, kVK_ANSI_R },
                { key_type::ALPHA_S, kVK_ANSI_S },
                { key_type::ALPHA_T, kVK_ANSI_T },
                { key_type::ALPHA_U, kVK_ANSI_U },
                { key_type::ALPHA_V, kVK_ANSI_V },
                { key_type::ALPHA_W, kVK_ANSI_W },
                { key_type::ALPHA_X, kVK_ANSI_X },
                { key_type::ALPHA_Y, kVK_ANSI_Y },
                { key_type::ALPHA_Z, kVK_ANSI_Z },
                { key_type::NUMERIC_0, kVK_ANSI_0 },
                { key_type::NUMERIC_1, kVK_ANSI_1 },
                { key_type::NUMERIC_2, kVK_ANSI_2 },
                { key_type::NUMERIC_3, kVK_ANSI_3 },
                { key_type::NUMERIC_4, kVK_ANSI_4 },
                { key_type::NUMERIC_5, kVK_ANSI_5 },
                { key_type::NUMERIC_6, kVK_ANSI_6 },
                { key_type::NUMERIC_7, kVK_ANSI_7 },
                { key_type::NUMERIC_8, kVK_ANSI_8 },
                { key_type::NUMERIC_9, kVK_ANSI_9 }
            };

            const auto it = map.find(type);

            if (it == map.end()) {
                return 0x00;
            }

            return it->second;
        }

        void flush(const bool is_key_down) override
        {
            std::queue<key_type>& keys = this->keys();
            if (keys.empty()) {
                return;
            }

            CGEventSourceRef source = CGEventSourceCreate(kCGEventSourceStateCombinedSessionState);

            while (!keys.empty()) {
                const CGKeyCode virtual_key = get_virtual_key(keys.front());

                if (is_key_down) {
                    key_down(source, virtual_key);
                }
                else {
                    key_up(source, virtual_key);
                }

                keys.pop();
            }

            CFRelease(source);
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
