#pragma once

#include <memory>
#include <stdexcept>

#ifdef _WIN64
#include "impl/windows_input_api.hpp"
#elif __APPLE__
#include "impl/apple_input_api.hpp"
#endif


namespace midikeys::input_api_factory
{
    inline std::unique_ptr<input_api> make_platform_default() {
#ifdef _WIN64
        return std::make_unique<windows_input_api>();
#elif __APPLE__
        return std::make_unique<apple_input_api>();
#endif

        throw std::runtime_error("Unsupported platform.");
    }
}
