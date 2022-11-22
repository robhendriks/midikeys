#include "input_mapping.hpp"
#include <spdlog/spdlog.h>
#include <yaml-cpp/yaml.h>
#include <algorithm>

namespace midikeys
{
    input_mapping::input_mapping() : m_channels()
    {
    }

    std::unique_ptr<input_mapping> input_mapping::from_yaml_file(const std::filesystem::path& path)
    {
        spdlog::debug("Load TOML mapping '{}'", path.string());

        auto mapping = std::make_unique<input_mapping>();

        if (!std::filesystem::is_regular_file(path)) {
            return mapping;
        }

        // TODO

        return mapping;
    }

    const input_binding* input_mapping::get_binding(uint8_t channel, uint8_t control) const
    {
        const auto channel_it = m_channels.find(channel);

        if (channel_it == m_channels.end()) {
            return nullptr;
        }

        const auto& controls = channel_it->second;
        const auto control_it = controls.find(control);
        if (control_it == controls.end()) {
            return nullptr;
        }

        const auto& binding = control_it->second;
        return &binding;
    }

    void input_mapping::set_binding(uint8_t channel, uint8_t control, input_binding binding)
    {
        const auto channel_it = m_channels.find(channel);
        if (channel_it == m_channels.end())
        {
            m_channels[channel] = {
                {control, std::move(binding)}
            };
        }
        else
        {
            channel_it->second[control] = std::move(binding);
        }
    }
}
