#pragma once

#include <filesystem>
#include "device_message.hpp"

namespace fs = std::filesystem;

namespace midikeys
{
    struct device_input_mapping
    {
        device_message_type midi_message_type;
        uint8_t midi_channel;
        uint8_t midi_control;
        std::vector<std::string> keys;
        std::string color_on;
        std::string color_off;
    };

    struct device_mapping
    {
        std::vector<device_input_mapping> inputs;

        static device_mapping from_yaml_file(const fs::path& file_path);
    };
}
