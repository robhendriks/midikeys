#pragma once

#include <argh.h>
#include <memory>
#include <filesystem>
#include "midi/midi_api.hpp"
#include "device/device_manager.hpp"

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

    class app : public std::enable_shared_from_this<app>, public midi_listener {
        const app_paths m_paths;
        std::unique_ptr<midi_api> m_midi_api;
        std::unique_ptr<midi_device> m_midi_device;
        std::unique_ptr<device_manager> m_device_manager;

        void run_command_root(const argh::parser& cmdl);

        void run_command_verify(const argh::parser& cmdl);

        void run_command_list(const argh::parser& cmdl);

        void configure(const app_options& options);

        bool initialize_device_manager(const argh::parser& cmdl);

        bool initialize_midi_api(const argh::parser& cmdl);

        void handle_open(const midi_device& device) override;

        void handle_message(const midi_device& device, const midi_message& message) override;

        void handle_close(const midi_device& device) override;

    public:
        app(app_paths paths) noexcept;

        void run(const char** argv);
    };
}

