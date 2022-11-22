#pragma once

#include "input_binding.hpp"
#include <unordered_map>
#include <filesystem>

namespace midikeys
{
    class input_mapping
    {
        std::unordered_map<uint8_t, std::unordered_map<uint8_t, input_binding>> m_channels;
    public:
        input_mapping();

        static std::unique_ptr<input_mapping> from_yaml_file(const std::filesystem::path& path);

        const input_binding* get_binding(uint8_t channel, uint8_t control) const;

        void set_binding(uint8_t channel, uint8_t control, input_binding binding);
    };
}
