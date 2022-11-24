#pragma once

#include <string>
#include <unordered_map>

namespace midikeys
{
	enum key_type
	{
		NONE,

		// - Win (Windows)
		// - Command (Apple)
		SUPER,

		SHIFT,
		CONTROL,

		// - Alt (Windows)
		// - Option (Apple)
		MENU,

		// Function keys
		F1,
		F2,
		F3,
		F4,
		F5,
		F6,
		F7,
		F8,
		F9,
		F10,
		F11,
		F12,

		ARROW_LEFT,
		ARROW_RIGHT,
		ARROW_UP,
		ARROW_DOWN,

		// Alpha
		ALPHA_A,
		ALPHA_B,
		ALPHA_C,
		ALPHA_D,
		ALPHA_E,
		ALPHA_F,
		ALPHA_G,
		ALPHA_H,
		ALPHA_I,
		ALPHA_J,
		ALPHA_K,
		ALPHA_L,
		ALPHA_M,
		ALPHA_N,
		ALPHA_O,
		ALPHA_P,
		ALPHA_Q,
		ALPHA_R,
		ALPHA_S,
		ALPHA_T,
		ALPHA_U,
		ALPHA_V,
		ALPHA_W,
		ALPHA_X,
		ALPHA_Y,
		ALPHA_Z,

		// Numeric
		NUMERIC_0,
		NUMERIC_1,
		NUMERIC_2,
		NUMERIC_3,
		NUMERIC_4,
		NUMERIC_5,
		NUMERIC_6,
		NUMERIC_7,
		NUMERIC_8,
		NUMERIC_9
	};

	static key_type key_type_from_string(const std::string& str) {
		static std::unordered_map<std::string, key_type> map{
			{ "super", key_type::SUPER },
			{ "shift", key_type::SHIFT },
			{ "ctrl", key_type::CONTROL },
			{ "menu", key_type::MENU },
			{ "f1", key_type::F1 },
			{ "f2", key_type::F2 },
			{ "f3", key_type::F3 },
			{ "f4", key_type::F4 },
			{ "f5", key_type::F5 },
			{ "f6", key_type::F6 },
			{ "f7", key_type::F7 },
			{ "f8", key_type::F8 },
			{ "f9", key_type::F9 },
			{ "f10", key_type::F10 },
			{ "f11", key_type::F11 },
			{ "f12", key_type::F12 },
			{ "arrow_left", key_type::ARROW_LEFT },
			{ "arrow_right", key_type::ARROW_RIGHT },
			{ "arrow_up", key_type::ARROW_UP },
			{ "arrow_down", key_type::ARROW_DOWN },
			{ "a", key_type::ALPHA_A },
			{ "b", key_type::ALPHA_B },
			{ "c", key_type::ALPHA_C },
			{ "d", key_type::ALPHA_D },
			{ "e", key_type::ALPHA_E },
			{ "f", key_type::ALPHA_F },
			{ "g", key_type::ALPHA_G },
			{ "h", key_type::ALPHA_H },
			{ "i", key_type::ALPHA_I },
			{ "j", key_type::ALPHA_J },
			{ "k", key_type::ALPHA_K },
			{ "l", key_type::ALPHA_L },
			{ "m", key_type::ALPHA_M },
			{ "n", key_type::ALPHA_N },
			{ "o", key_type::ALPHA_O },
			{ "p", key_type::ALPHA_P },
			{ "q", key_type::ALPHA_Q },
			{ "r", key_type::ALPHA_R },
			{ "s", key_type::ALPHA_S },
			{ "t", key_type::ALPHA_T },
			{ "u", key_type::ALPHA_U },
			{ "v", key_type::ALPHA_V },
			{ "w", key_type::ALPHA_W },
			{ "x", key_type::ALPHA_X },
			{ "y", key_type::ALPHA_Y },
			{ "z", key_type::ALPHA_Z },
			{ "0", key_type::NUMERIC_0 },
			{ "1", key_type::NUMERIC_1 },
			{ "2", key_type::NUMERIC_2 },
			{ "3", key_type::NUMERIC_3 },
			{ "4", key_type::NUMERIC_4 },
			{ "5", key_type::NUMERIC_5 },
			{ "6", key_type::NUMERIC_6 },
			{ "7", key_type::NUMERIC_7 },
			{ "8", key_type::NUMERIC_8 },
		};

		const auto it = map.find(str);

		if (it == map.end()) {
			return key_type::NONE;
		}

		return it->second;
	}

	struct keyboard_event
	{
		mutable std::vector<key_type> key_types;
	};
}
