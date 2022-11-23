#pragma once

#include <filesystem>
#include "device_message.hpp"
#include "../midi/midi_map.hpp"
#include "../input/keyboard_event.hpp"

namespace fs = std::filesystem;

namespace midikeys
{
	enum device_control_type
	{
		BUTTON,
		ENCODER
	};

	struct device_input_mapping
	{
		device_control_type control_type;
		uint8_t midi_channel;
		uint8_t midi_control;
		std::vector<key_type> keys;
		std::string color_on;
		std::string color_off;

		const std::string& get_color(const bool is_pressed) const;
	};

	struct device_mapping
	{
		midi_map<device_input_mapping> inputs;

		static device_mapping from_yaml_file(const fs::path& file_path);
	};
}
