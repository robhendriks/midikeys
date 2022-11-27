#pragma once

#include <vector>
#include <iostream>

namespace midikeys
{
    struct device_configuration
    {
        size_t input;
        size_t output;
    };

    struct configuration
    {
        std::vector<device_configuration> devices;
    };
}
