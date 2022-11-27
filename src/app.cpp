#include "app.hpp"
#include "midi/midi_api_factory.hpp"
#include "input/input_api_factory.hpp"
#include <spdlog/spdlog.h>

namespace midikeys
{
    app::app(app_paths paths)
        : m_paths(std::move(paths)),
        m_configuration_manager(),
        m_midi_device_manager()
    {
    }

    app_options app::get_app_options(const argh::parser& cmdl)
    {
#ifdef NDEBUG
        bool verbose = cmdl[{"-v", "--verbose"}];
#else
        bool verbose = true;
#endif

        return { verbose };
    }

    void app::apply_app_options(const app_options& options)
    {
        if (options.verbose) {
            spdlog::set_level(spdlog::level::debug);
        }
    }

    fs::path app::resolve_config_path(const argh::parser& cmdl)
    {
        std::string config_path_str = cmdl({ "-c", "--config" }).str();

        if (!config_path_str.empty()) {
            return fs::path(config_path_str);
        }

        return m_paths.root / "config.yml";
    }

    bool app::try_load_config(const fs::path& config_path)
    {
        try {
            m_configuration_manager.load(config_path);
            return true;
        }
        catch (const std::exception& e) {
            spdlog::error("Unable to load configuration");
            spdlog::error(e.what());
            return false;
        }
    }

    bool app::try_initialize_midi()
    {
        try {
            m_midi_device_manager.create_api();
            m_midi_device_manager.create_devices(m_configuration_manager.config()->devices);

            return true;
        }
        catch (const std::exception& e) {
            spdlog::error("Unable to initialize MIDI");
            spdlog::error(e.what());
            return false;
        }
    }

    void app::run_loop()
    {
        m_midi_device_manager.open_device_connections();

        char c;
        std::cin.get(c);

        m_midi_device_manager.close_device_connections();
    }

    int app::run(const char* argv[])
    {
        const auto cmdl = argh::parser(argv);

        apply_app_options(get_app_options(cmdl));

        if (!try_load_config(resolve_config_path(cmdl)) ||
            !try_initialize_midi()) {
            return 1;
        }

        run_loop();

        // TODO

        return 0;
    }
}
