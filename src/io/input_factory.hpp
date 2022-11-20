#pragma once

#include <memory>
#include <stdexcept>
#include "input_handler.hpp"
#include "windows_input_handler.hpp"

namespace midikeys::input_factory
{
    inline std::unique_ptr<midikeys::input_handler> make_platform_default()
    {
#ifdef _WIN64
        return std::make_unique<windows_input_handler>();
#else
        throw std::runtime_error("Unsupported platform.");
#endif
    }
}