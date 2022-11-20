#pragma once

#include <memory>
#include <string>
#include <string_view>

namespace midikeys
{
    class input_handler
    {
    public:
        virtual std::string_view platform() const = 0;
    };
}
