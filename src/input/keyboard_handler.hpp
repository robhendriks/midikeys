#pragma once

#include <queue>
#include "keyboard_event.hpp"

#include <queue>

namespace midikeys
{
	class keyboard_handler
	{
		std::queue<key_type> m_keys;

	public:
		keyboard_handler()
			: m_keys()
		{
		}

		void push(const key_type key)
		{
			m_keys.push(key);
		}

		virtual void flush() = 0;

		std::queue<key_type>& keys()
		{
			return m_keys;
		}
	};
}
