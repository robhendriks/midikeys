#pragma once

#include <memory>
#include <stdexcept>

#ifdef _WIN64
#include "impl/windows_input_api.hpp"
#endif //  _WIN64


namespace midikeys::input_api_factory
{
    inline std::unique_ptr<input_api> make_platform_default() {
#ifdef _WIN64
        return std::make_unique<windows_input_api>();
#endif // _WIN64

        throw std::runtime_error("Unsupported platform.");
    }
}
