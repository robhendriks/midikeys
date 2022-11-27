#pragma once

#include <yaml-cpp/yaml.h>
#include <spdlog/spdlog.h>
#include "configuration.hpp"

using namespace midikeys;

namespace YAML
{
    template<>
    struct convert<device_configuration>
    {
        static bool decode(const Node& node, device_configuration& device_cfg)
        {
            const Node& input_node = node["input"];
            const Node& output_node = node["output"];

            if (!input_node.IsScalar() || !output_node.IsScalar()) {
                return false;
            }

            device_cfg.input = input_node.as<size_t>();
            device_cfg.output = output_node.as<size_t>();

            return true;
        }
    };

    template<>
    struct convert<configuration>
    {
        static bool decode(const Node& node, configuration& cfg)
        {
            const Node& devices_node = node["devices"];

            cfg.devices = devices_node.as<std::vector<device_configuration>>();

            return true;
        }
    };
}
