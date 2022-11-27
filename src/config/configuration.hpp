#pragma once

#include <vector>
#include <iostream>

#include "device_configuration.hpp"

namespace midikeys
{
    struct configuration
    {
        std::vector<device_configuration> devices;
    };
}
