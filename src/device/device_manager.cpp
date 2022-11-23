#include "device_manager.hpp"
#include "../midi/midi_device.hpp"
#include <stdexcept>
#include <spdlog/spdlog.h>
#include <algorithm>

namespace midikeys
{
	void device_state::initialize(device_mapping& mapping)
	{
		for (auto& input : mapping.inputs) {
			input_states[input.first] = false;
		}
	}

	device_manager::device_manager() {}

	void device_manager::midi_update(const midi_device& device) const
	{
		for (const auto& it : m_state.input_states) {
			const bool is_pressed = it.second;

			const auto input_it = m_mapping.inputs.find(it.first);
			if (input_it == m_mapping.inputs.end()) {
				continue;
			}

			const std::string& color = input_it->second.get_color(is_pressed);

			const uint8_t color_midi_value = m_profile.color_map.get_color_or_default(color, 0);


			const auto message = midi_message::make_control_change(
				input_it->second.midi_channel,
				input_it->second.midi_control,
				color_midi_value);

			device.output().send_message(message);
		}
	}

	bool device_manager::try_load_mapping(const fs::path& path)
	{
		try {
			m_mapping = device_mapping::from_yaml_file(path);
			m_state.initialize(m_mapping);

			return true;
		}
		catch (const std::exception& e) {
			spdlog::error("Invalid mapping '{}': {}", path.string(), e.what());
			return false;
		}
	}

	bool device_manager::try_load_profile(const fs::path& path)
	{
		try {
			m_profile = device_profile::from_yaml_file(path);
			return true;
		}
		catch (const std::exception& e) {
			spdlog::error("Invalid profile '{}': {}", path.string(), e.what());
			return false;
		}
	}

	void device_manager::handle_open(const midi_device& device)
	{
		for (const auto& msg : m_profile.message_map.open) {
			device.output().send_message(static_cast<midi_message>(msg));
		}

		midi_update(device);
	}

	void device_manager::handle_message(const midi_device& device, const midi_message& message)
	{
		if (message.type() != message_type::NOTE_ON && message.type() != message_type::NOTE_OFF) {
			return;
		}

		const uint8_t channel = message.channel();
		const uint8_t control = message.at(1);
		const uint8_t velocity = message.at(2);

		const bool is_pressed = velocity > 0;

		const midi_key key = midi_key{ channel, control };
		const auto input_state_it = m_state.input_states.find(key);

		if (input_state_it != m_state.input_states.end()) {
			m_state.input_states[key] = is_pressed;
			midi_update(device);
		}
	}

	void device_manager::handle_close(const midi_device& device)
	{
		for (const auto& msg : m_profile.message_map.close) {
			device.output().send_message(static_cast<midi_message>(msg));
		}
	}

	const device_mapping& device_manager::mapping() const
	{
		return m_mapping;
	}

	const device_profile& device_manager::profile() const
	{
		return m_profile;
	}
}