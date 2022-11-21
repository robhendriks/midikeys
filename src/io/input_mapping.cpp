#include "input_mapping.hpp"
#include <spdlog/spdlog.h>
#include <toml++/toml.h>
#include <algorithm>

namespace midikeys
{
    input_mapping::input_mapping() : m_channels()
    {
    }

    std::unique_ptr<input_mapping> input_mapping::from_toml_file(const std::filesystem::path& path)
    {
        spdlog::debug("Load TOML mapping '{}'", path.string());

        auto mapping = std::make_unique<input_mapping>();

        if (!std::filesystem::is_regular_file(path)) {
            return mapping;
        }

        const toml::table t_root = toml::parse_file(path.string());
        const toml::node_view<const toml::node> t_inputs = t_root["inputs"];

        if (t_inputs.is_array())
        {
            const toml::array& t_inputs_arr = *t_inputs.as_array();

            spdlog::debug("Loading {} input binding(s)", t_inputs_arr.size());

            for (const toml::node& node : t_inputs_arr)
            {
                if (!node.is_table()) {
                    continue;
                }

                const toml::table& t_input_tbl = *node.as_table();

                const uint8_t channel = t_input_tbl["channel"].value_or(0);
                const uint8_t control = t_input_tbl["control"].value_or(0);
                const bool mod_super = t_input_tbl["mod_super"].value_or(false);
                const bool mod_ctrl = t_input_tbl["mod_ctrl"].value_or(false);
                const bool mod_alt = t_input_tbl["mod_alt"].value_or(false);
                const bool mod_shift = t_input_tbl["mod_shift"].value_or(false);
                
                const std::string key = t_input_tbl["key"].value_or("");

                keyboard_code code = key_from_string(key);
                keyboard_modifiers modifiers = make_modifier(mod_super, mod_ctrl, mod_alt, mod_shift);

                mapping->set_binding(channel, control, { code, modifiers });
            }
        }

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