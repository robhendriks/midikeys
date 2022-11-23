#pragma once

#include "device_mapping_yaml.hpp"
#include "device_message_yaml.hpp"
#include <yaml-cpp/yaml.h>
#include <spdlog/spdlog.h>
#include <stdexcept>
#include <unordered_map>

namespace YAML
{
	template<>
	struct convert<midikeys::device_input_mapping> {
		static Node encode(const midikeys::device_input_mapping& input)
		{
			Node node;

			// TODO

			return node;
		}

		static bool decode(const Node& node, midikeys::device_input_mapping& input)
		{
			if (!node.IsMap()) {
				return false;
			}

			for (const auto& child : node) {
				const Node& key = child.first;
				const Node& value = child.second;

				if (!key.IsScalar() || !value.IsMap()) {
					break;
				}

				input.midi_message_type = convert<midikeys::device_message>::type_from_string(key.as<std::string>());
				input.midi_channel = value["channel"].as<uint8_t>();
				input.midi_control = value["control"].as<uint8_t>();

				const Node& keys = value["keys"];
				if (keys.IsSequence()) {
					input.keys = keys.as<std::vector<std::string>>();
				}
				else if (keys.IsScalar()) {
					input.keys = { keys.as<std::string>() };
				}

				const Node& color = value["color"];
				if (color.IsScalar()) {
					input.color_on = color.as<std::string>() + "_on";
					input.color_off = color.as<std::string>() + "_off";
				}

				break;
			}

			return true;
		}
	};

	template<>
	struct convert<midikeys::device_mapping> {
		static Node encode(const midikeys::device_mapping& mapping)
		{
			Node node;

			// TODO

			return node;
		}

		static bool decode(const Node& node, midikeys::device_mapping& mapping)
		{
			if (!node.IsSequence()) {
				return false;
			}

			for (const auto& child : node) {
				midikeys::device_input_mapping input_mapping = child.as<midikeys::device_input_mapping>();

				mapping.inputs[midikeys::midi_key{ input_mapping.midi_channel,input_mapping.midi_control }] = std::move(input_mapping);
			}

			return true;
		}
	};
}
