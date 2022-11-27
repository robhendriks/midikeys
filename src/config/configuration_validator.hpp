#pragma once

#include "configuration.hpp"

#include <vector>
#include <string>
#include <unordered_map>

namespace midikeys::configuration_validator
{
    struct configuration_validator_result
    {
        std::vector<std::string> errors;
    };

    inline void validate_port_usage(const configuration& cfg, const configuration_validator_result& result)
    {
        // TODO: implement logic to detect ports that are being used more than once
    }

    inline configuration_validator_result validate(const configuration& cfg)
    {
        configuration_validator_result result;

        validate_port_usage(cfg, result);

        return result;
    }
}
