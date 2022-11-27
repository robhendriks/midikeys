#pragma once

#include "configuration.hpp"
#include <spdlog/fmt/fmt.h>

namespace midikeys::configuration_util
{
    template<typename... T>
    inline std::string make_error_message(const device_configuration& device_cfg, fmt::format_string<T...> fmt, T&&... args)
    {
        return fmt::format(
            "Error in device configuration '{}': {}",
            device_cfg.name,
            fmt::format(fmt, args...));
    }
}
