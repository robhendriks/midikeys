#pragma once

#include "device_mapping.hpp"
#include "device_profile.hpp"
#include "../midi/midi_listener.hpp"
#include <memory>
#include <filesystem>
#include <unordered_map>

namespace fs = std::filesystem;

namespace midikeys
{
    struct device_state
    {
        std::unordered_map<int, std::tuple<device_input_mapping*, bool>> input_states;

        static int make_key(const size_t channel, const size_t control);

        void initialize(device_mapping& mapping);
    };

    class device_manager : public midi_listener
    {
        device_mapping m_mapping;
        device_profile m_profile;
        device_state m_state;

        void midi_update(const midi_device& device) const;

    public:
        device_manager();

        bool try_load_mapping(const fs::path& path);
        bool try_load_profile(const fs::path& path);

        void handle_open(const midi_device& device) override;
        void handle_message(const midi_device& device, const midi_message& message) override;
        void handle_close(const midi_device& device) override;

        const device_mapping& mapping() const;
        const device_profile& profile() const;
    };
}
