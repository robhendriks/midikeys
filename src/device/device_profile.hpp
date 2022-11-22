#pragma once

#include <unordered_map>
#include <filesystem>
#include <stdexcept>
#include <yaml-cpp/yaml.h>

namespace fs = std::filesystem;

namespace midikeys
{
    enum device_message_type
    {
        UNKNOWN,
        CONTROL_CHANGE,
        SYSEX
    };

    struct device_message
    {
        device_message_type type;
        std::vector<uint8_t> args;
    };

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
