#include "device_mapping.hpp"
#include "device_mapping_yaml.hpp"
#include <yaml-cpp/yaml.h>
#include <spdlog/spdlog.h>

namespace midikeys
{
	const std::string& device_input_mapping::get_color(const bool is_pressed) const
	{
		return is_pressed
			? color_on
			: color_off;
	}

	device_mapping device_mapping::from_yaml_file(const fs::path& file_path)
	{
		spdlog::debug("Loading device mapping '{}'", file_path.string());

		YAML::Node node = YAML::LoadFile(file_path.string());

		if (node.IsMap() && node["mapping"]) {
			return node["mapping"].as<device_mapping>();
		}

		return {};
	}
}
