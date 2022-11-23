#pragma once

#include <unordered_map>

namespace midikeys
{
	struct midi_key
	{
		const uint8_t channel;
		const uint8_t control;

		bool operator==(const midi_key& other) const
		{
			return channel == other.channel && control == other.control;
		}
	};

	template<class T>
	class midi_map : public std::unordered_map<midi_key, T>
	{
	};
}

namespace std {
	template <>
	struct hash<midikeys::midi_key> {
		auto operator()(const midikeys::midi_key& key) const -> size_t {
			return hash<uint8_t>()(key.channel) ^
				hash<uint8_t>()(key.control);
		}
	};
}
