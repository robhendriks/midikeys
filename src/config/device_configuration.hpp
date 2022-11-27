#pragma once

#include <vector>
#include <iostream>

namespace midikeys
{
    struct device_configuration
    {
        std::string name;
        size_t input;
        size_t output;
    };
}
