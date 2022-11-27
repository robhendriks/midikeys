#include "configuration_manager.hpp"
#include "configuration_yaml.hpp"
#include "configuration_validator.hpp"
#include <yaml-cpp/yaml.h>
#include <spdlog/spdlog.h>

namespace midikeys
{
    configuration_manager::configuration_manager()
        : m_config(nullptr)
    {
    }

    void configuration_manager::validate(const configuration& config)
    {
        const auto& validation_result = configuration_validator::validate(config);

        if (!validation_result.errors.empty()) {
            throw std::runtime_error("Configuration validation failed: " + validation_result.errors.front());
        }
    }

    void configuration_manager::load(const fs::path& path)
    {
        if (!fs::is_regular_file(path)) {
            throw std::runtime_error("File not found: " + path.string());
        }

        const auto& node = YAML::LoadFile(path.string());

        m_config = std::make_unique<configuration>(node.as<configuration>());

        spdlog::debug("Loaded configuration from '{}'", path.string());

        validate(*m_config.get());
    }

    configuration* configuration_manager::config() const
    {
        return m_config.get();
    }
}
