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

                const Node& feedback = value["feedback"];
                if (feedback.IsMap()) {
                    input.color_on = feedback["on"].as<std::string>();
                    input.color_off = feedback["off"].as<std::string>();
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
                mapping.inputs.push_back(child.as<midikeys::device_input_mapping>());
            }

            return true;
        }
    };
}
