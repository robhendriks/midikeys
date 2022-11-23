#pragma once

#include "../midi/midi_message.hpp"
#include "device_message.hpp"
#include <unordered_map>
#include <filesystem>
#include <stdexcept>
#include <yaml-cpp/yaml.h>
#include <spdlog/fmt/fmt.h>

namespace fs = std::filesystem;

namespace midikeys
{
    struct device_message_map
    {
        std::vector<device_message> open;
        std::vector<device_message> close;
    };

    struct device_color_map : public std::unordered_map<std::string, uint8_t>
    {
    };

    struct device_profile
    {
        device_color_map color_map;
        device_message_map message_map;

        static device_profile from_yaml_file(const fs::path& file_path);
    };
}
