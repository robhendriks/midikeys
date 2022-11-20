#include "windows_input_handler.hpp"

namespace midikeys
{
    const std::string windows_input_handler::s_platform = "Windows";

    std::string_view windows_input_handler::platform() const
    {
        return s_platform;
    }
}