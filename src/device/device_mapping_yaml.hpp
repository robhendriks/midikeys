#pragma once

#include "device_mapping_yaml.hpp"
#include "device_message_yaml.hpp"
#include <yaml-cpp/yaml.h>
#include <spdlog/spdlog.h>
#include <stdexcept>
#include <unordered_map>
#include <ranges>

namespace YAML
{
    template<>
    struct convert<midikeys::key_type> {
        static Node encode(const midikeys::key_type& mapping)
        {
            Node node;

            // TODO

            return node;
        }

        static bool decode(const Node& node, midikeys::key_type& key_type)
        {
            if (!node.IsScalar()) {
                return false;
            }

            const std::string key_type_str = node.as<std::string>();

            key_type = midikeys::key_type_from_string(key_type_str);

            return key_type != midikeys::NONE;
        }
    };

    template<>
    struct convert<std::vector<midikeys::device_input_mapping>> {
        static midikeys::device_control_type control_type_from_string(const std::string& str)
        {
            static std::unordered_map<std::string, midikeys::device_control_type> map{
                {"button", midikeys::BUTTON},
                {"encoder", midikeys::ENCODER}
            };

            const auto it = map.find(str);

            if (it == map.end()) {
                throw std::out_of_range(fmt::format("Invalid control type: {}", str));
            }

            return it->second;
        }

        static Node encode(const std::vector<midikeys::device_input_mapping>& inputs)
        {
            Node node;

            // TODO

            return node;
        }

        static void decode_range(const Node& value_node, std::vector<midikeys::device_input_mapping>& inputs)
        {
            const midikeys::device_control_type control_type
                = control_type_from_string(value_node["type"].as<std::string>(""));

            const Node& midi_node = value_node["midi"];
            const Node& keyboard_node = value_node["keyboard"];
            const Node& color_node = value_node["color"];

            if (!midi_node.IsMap() || !keyboard_node.IsSequence() || !color_node.IsScalar()) {
                return;
            }

            const std::vector<midikeys::key_type> keyboard = keyboard_node.as<std::vector<midikeys::key_type>>();
            const std::string color = color_node.as<std::string>("white");

            const Node& midi_channel_node = midi_node["channel"];
            const Node& midi_control_range_node = midi_node["control"];

            if (!midi_channel_node.IsScalar() || !midi_control_range_node.IsSequence() || midi_control_range_node.size() != 2) {
                return;
            }

            const uint8_t midi_channel = midi_channel_node.as<uint8_t>();

            const uint8_t midi_control_range_start = midi_control_range_node[0].as<uint8_t>(0);
            const uint8_t midi_control_range_end = midi_control_range_node[1].as<uint8_t>(0) + 1;

            const size_t midi_control_range_size = midi_control_range_end - midi_control_range_start;

            if (midi_control_range_size < 1 || midi_control_range_size != keyboard.size()) {
                return;
            }

            size_t i = 0;
            for (const uint8_t midi_control : std::views::iota(midi_control_range_start, midi_control_range_end)) {
                midikeys::device_input_mapping input;

                input.control_type = control_type;
                input.midi_channel = midi_channel;
                input.midi_control = midi_control;
                input.color_off = color + "_off";
                input.color_on = color + "_on";
                input.keys = { keyboard.at(i++) };

                inputs.push_back(std::move(input));
            }
        }

        static void decode_single(const std::string& key, const Node& valueNode, std::vector<midikeys::device_input_mapping>& inputs)
        {
            midikeys::device_input_mapping input;

            const Node& midiNode = valueNode["midi"];
            if (midiNode.IsSequence() && midiNode.size() == 2) {
                input.midi_channel = midiNode[0].as<uint8_t>();
                input.midi_control = midiNode[1].as<uint8_t>();
            }
            else if (midiNode.IsMap()) {
                input.midi_channel = midiNode["channel"].as<uint8_t>();
                input.midi_control = midiNode["control"].as<uint8_t>();
            }

            input.control_type = control_type_from_string(key);

            const Node& keyboardNode = valueNode["keyboard"];

            if (keyboardNode.IsSequence()) {
                input.keys = keyboardNode.as<std::vector<midikeys::key_type>>();
            }
            else if (keyboardNode.IsScalar()) {
                input.keys = { keyboardNode.as<midikeys::key_type>() };
            }

            const Node& colorNode = valueNode["color"];
            if (colorNode.IsScalar()) {
                input.color_off = colorNode.as<std::string>() + "_off";
                input.color_on = colorNode.as<std::string>() + "_on";
            }
            else if (colorNode.IsSequence() && colorNode.size() == 2) {
                input.color_off = colorNode[0].as<std::string>() + "_off";
                input.color_on = colorNode[1].as<std::string>() + "_on";
            }

            inputs.push_back(std::move(input));
        }

        static bool decode(const Node& node, std::vector<midikeys::device_input_mapping>& inputs)
        {
            if (!node.IsMap()) {
                return false;
            }

            for (const auto& child : node) {
                const Node& keyNode = child.first;
                const Node& valueNode = child.second;

                if (!keyNode.IsScalar() || !valueNode.IsMap()) {
                    break;
                }

                const std::string key = keyNode.as<std::string>();

                if (key == "range") {
                    decode_range(valueNode, inputs);
                }
                else {
                    decode_single(key, valueNode, inputs);
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
                const auto input_mappings = child.as<std::vector<midikeys::device_input_mapping>>();

                for (const auto& input_mapping : input_mappings) {
                    mapping.inputs[midikeys::midi_key{
                        input_mapping.midi_channel,
                        input_mapping.midi_control }] = std::move(input_mapping);
                }
            }

            return true;
        }
    };
}
