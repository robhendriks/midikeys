#pragma once

#include <filesystem>

namespace fs = std::filesystem;

namespace midikeys
{
    struct app_paths {
        const fs::path root;
        const fs::path mapping_dir_path;
        const fs::path profile_dir_path;

        static app_paths make_default();

        fs::path get_mapping_path(const std::string& name) const;
        fs::path get_profile_path(const std::string& name) const;
    };
}
