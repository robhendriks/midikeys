#pragma once

#include "device_profile.hpp"
#include <yaml-cpp/yaml.h>
#include <spdlog/spdlog.h>
#include <stdexcept>

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
                color_map[it.first.as<std::string>()] = it.second.as<uint8_t>();
            }

            return true;
        }
    };

    template<>
    struct convert<midikeys::device_message> {
        static Node encode(const midikeys::device_message& message)
        {
            Node node;

            // TODO

            return node;
        }

        static midikeys::device_message_type type_from_string(const std::string& str)
        {
            if (str == "sysex") {
                return midikeys::SYSEX;
            }
            else if (str == "control_change") {
                return midikeys::CONTROL_CHANGE;
            }
            else {
                return midikeys::UNKNOWN;
            }
        }

        static bool decode(const Node& node, midikeys::device_message& message)
        {
            if (!node.IsMap()) {
                return false;
            }

            for (const auto& it : node) {

                message.type = type_from_string(it.first.as<std::string>());

                if (it.second.IsSequence()) {
                    message.args = it.second.as<std::vector<uint8_t>>();
                }
                else if (it.second.IsMap()) {
                    const Node& argsNode = it.second["args"];

                    if (argsNode && argsNode.IsSequence()) {
                        message.args = argsNode.as<std::vector<uint8_t>>();
                    }
                }

                // Only process a single entry
                break;
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
                    messages.emplace_back(midikeys::SYSEX, it.as<std::vector<uint8_t>>());
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
