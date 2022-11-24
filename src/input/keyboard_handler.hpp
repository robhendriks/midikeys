#pragma once

#include <vector>
#include "keyboard_event.hpp"

namespace midikeys
{
	class keyboard_handler
	{
	public:
		virtual void handle_event(const keyboard_event& evt) const = 0;
	};
}
