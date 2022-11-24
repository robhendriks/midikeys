#pragma once

#include "device_mapping.hpp"
#include "device_profile.hpp"
#include "../midi/midi_listener.hpp"
#include "../input/input_api.hpp"
#include <memory>
#include <filesystem>
#include <unordered_map>

namespace fs = std::filesystem;

namespace midikeys
{
	class app;

	struct device_state
	{
		midi_map<bool> input_states;

		void initialize(device_mapping& mapping);
	};

	class device_manager : public midi_listener
	{
		std::unique_ptr<input_api> m_input_api;

		device_mapping m_mapping;
		device_profile m_profile;
		device_state m_state;

		void midi_update(const midi_device& device) const;
		void input_update(const midi_key key);

		void handle_internal_key(const key_type key);

	public:
		device_manager(const std::unique_ptr<input_api> input_api);

		bool try_load_mapping(const fs::path& path);
		bool try_load_profile(const fs::path& path);

		void handle_open(const midi_device& device) override;
		void handle_message(const midi_device& device, const midi_message& message) override;
		void handle_close(const midi_device& device) override;

		const device_mapping& mapping() const;
		const device_profile& profile() const;
	};
}
