#pragma once

#include <filesystem>
#include "configuration.hpp"

namespace fs = std::filesystem;

namespace midikeys
{
    class configuration_manager
    {
        std::unique_ptr<configuration> m_config;

        static void validate(const configuration& config);

    public:
        configuration_manager();

        void load(const fs::path& path);

        configuration* config() const;
    };
}
