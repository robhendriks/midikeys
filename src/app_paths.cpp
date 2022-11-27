#include "app_paths.hpp"

namespace midikeys
{
    app_paths app_paths::make_default()
    {
        const fs::path root = fs::current_path();

        return {
            root,
            root / "mappings",
            root / "profiles"
        };
    }

    fs::path app_paths::get_mapping_path(const std::string& name) const
    {
        return mapping_dir_path / (name + ".yml");
    }

    fs::path app_paths::get_profile_path(const std::string& name) const
    {
        return profile_dir_path / (name + ".yml");
    }
}
