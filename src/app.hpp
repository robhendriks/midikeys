#pragma once

#include <argh.h>
#include <memory>
#include "midi/midi_api.hpp"

namespace midikeys {
    struct app_options {
        const bool verbose;

        static app_options from_cmdl(const argh::parser &cmdl);
    };

    class app {
        std::unique_ptr<midi_api> m_midi_api;
        std::unique_ptr<midi_device> m_midi_device;

        void run_command_root(const argh::parser &cmdl);

        void run_command_list(const argh::parser &cmdl);

        void configure(const app_options &options);

        void initialize_midi_api();

        bool try_initialize_midi_api();

    public:
        app() noexcept;

        void run(const char **argv);
    };
}

