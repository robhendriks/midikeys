#pragma once

#include <argh.h>
#include <memory>
#include <filesystem>
#include "midi/midi_api.hpp"

namespace fs = std::filesystem;

namespace midikeys {
    struct app_paths {
        const fs::path root;
        const fs::path mapping_dir_path;
        const fs::path profile_dir_path;

        static app_paths make_default();

        fs::path get_mapping_path(const std::string& name) const;
        fs::path get_profile_path(const std::string& name) const;
    };

    struct app_options {
        const bool verbose;

        static app_options from_cmdl(const argh::parser& cmdl);
    };

    class app {
        const app_paths m_paths;
        std::unique_ptr<midi_api> m_midi_api;
        std::unique_ptr<midi_device> m_midi_device;

        void run_command_root(const argh::parser& cmdl);

        void run_command_verify(const argh::parser& cmdl);

        void run_command_list(const argh::parser& cmdl);

        void configure(const app_options& options);

        void initialize_midi_api();

        bool try_initialize_midi_api();

    public:
        app(app_paths paths) noexcept;

        void run(const char** argv);
    };
}

