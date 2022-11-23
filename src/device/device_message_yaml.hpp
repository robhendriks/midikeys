#pragma once

#include "device_message.hpp"
#include <yaml-cpp/yaml.h>
#include <spdlog/spdlog.h>

namespace YAML
{
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
            static const std::unordered_map<std::string, midikeys::device_message_type> da{
                {"control_change", midikeys::CONTROL_CHANGE},
                {"note_on", midikeys::NOTE_ON},
                {"note_off", midikeys::NOTE_OFF},
                {"sysex", midikeys::SYSEX}
            };

            const auto it = da.find(str);
            if (it == da.end()) {
                return midikeys::UNKNOWN;
            }

            return it->second;
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
}
