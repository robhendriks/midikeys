#pragma once

#include "device_profile.hpp"
#include "device_message.hpp"
#include "device_message_yaml.hpp"
#include <yaml-cpp/yaml.h>
#include <spdlog/spdlog.h>
#include <stdexcept>
#include <unordered_map>

namespace YAML
{
	template<>
	struct convert<midikeys::device_color_map> {
		static Node encode(const midikeys::device_color_map& color_map)
		{
			Node node;

			// TODO

			return node;
		}

		static bool decode(const Node& node, midikeys::device_color_map& color_map)
		{
			if (!node.IsMap()) {
				return false;
			}

			for (const auto& it : node) {
				const Node& keyNode = it.first;
				const Node& valueNode = it.second;

				if (keyNode.IsScalar() && valueNode.IsSequence() && valueNode.size() == 2) {
					const std::string key = keyNode.as<std::string>();

					color_map[key + "_off"] = it.second[0].as<uint8_t>();
					color_map[key + "_on"] = it.second[1].as<uint8_t>();
				}

				
			}

			return true;
		}
	};

	template<>
	struct convert<midikeys::device_message_map> {
		static Node encode(const midikeys::device_message_map& message_map)
		{
			Node node;

			// TODO

			return node;
		}

		static void decode_message_sequence(const Node& node, std::vector<midikeys::device_message>& messages)
		{
			if (!node.IsSequence()) {
				return;
			}

			for (const auto& it : node) {
				if (it.IsSequence()) {
					messages.push_back({midikeys::SYSEX, it.as<std::vector<uint8_t>>()});
				}
				else if (it.IsMap()) {
					messages.push_back(it.as<midikeys::device_message>());
				}
			}
		}

		static bool decode(const Node& node, midikeys::device_message_map& message_map)
		{
			if (!node.IsMap()) {
				return false;
			}

			decode_message_sequence(node["open"], message_map.open);
			decode_message_sequence(node["close"], message_map.close);

			return true;
		}
	};

	template<>
	struct convert<midikeys::device_profile> {
		static Node encode(const midikeys::device_profile& profile)
		{
			Node node;

			// TODO

			return node;
		}

		static bool decode(const Node& node, midikeys::device_profile& profile)
		{
			if (!node.IsMap()) {
				return false;
			}

			if (node["colors"]) {
				profile.color_map = node["colors"].as<midikeys::device_color_map>();
			}

			if (node["messages"]) {
				profile.message_map = node["messages"].as<midikeys::device_message_map>();
			}

			return true;
		}
	};
}
