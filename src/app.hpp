#pragma once

#include <filesystem>
#include <argh.h>

#include "app_paths.hpp"
#include "config/configuration_manager.hpp"
#include "midi/midi_device_manager.hpp"

namespace fs = std::filesystem;

namespace midikeys {
    struct app_options {
        const bool verbose;
    };

    class app : public std::enable_shared_from_this<app> {
        const app_paths m_paths;
        configuration_manager m_configuration_manager;
        midi_device_manager m_midi_device_manager;

        static app_options get_app_options(const argh::parser& cmdl);

        void apply_app_options(const app_options& options);

        fs::path resolve_config_path(const argh::parser& cmdl);

        bool try_load_config(const fs::path& config_path);

        bool try_initialize_midi();

        void run_loop();
    public:
        app(app_paths paths);

        int run(const char** argv);
    };
}

