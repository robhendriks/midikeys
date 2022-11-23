#include "device_profile.hpp"
#include "device_profile_yaml.hpp"
#include <spdlog/spdlog.h>

namespace midikeys
{
	uint8_t device_color_map::get_color_or_default(const std::string& key, const uint8_t default_value) const
	{
		const auto it = this->find(key);

		if (it == end()) {
			return default_value;
		}

		return it->second;
	}

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
