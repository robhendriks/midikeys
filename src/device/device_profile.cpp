#include "device_profile.hpp"
#include "device_profile_yaml.hpp"
#include <spdlog/spdlog.h>

namespace midikeys
{
    device_profile device_profile::from_yaml_file(const fs::path& file_path)
    {
        spdlog::debug("Loading device profile '{}'", file_path.string());

        YAML::Node node = YAML::LoadFile(file_path.string());

        if (node.IsMap() && node["profile"]) {
            return node["profile"].as<device_profile>();
        }

        return {};
    }
}
