#pragma once

#include "../midi/midi_message.hpp"
#include <vector>
#include <stdexcept>
#include <spdlog/fmt/fmt.h>

namespace midikeys
{
    enum device_message_type
    {
        UNKNOWN,
        CONTROL_CHANGE,
        NOTE_ON,
        NOTE_OFF,
        SYSEX
    };

    struct device_message
    {
        device_message_type type;
        std::vector<uint8_t> args;

        operator midi_message() const
        {
            if (type == device_message_type::CONTROL_CHANGE) {
                if (args.size() != 3) {
                    throw std::runtime_error(fmt::format("CONTROL_CHANGE message requires exactly 3 arguments, {} given.", args.size()));
                }

                return midi_message::make_control_change(args.at(0), args.at(1), args.at(2));
            }
            else if (type == device_message_type::NOTE_ON) {
                if (args.size() != 3) {
                    throw std::runtime_error(fmt::format("NOTE_ON message requires exactly 3 arguments, {} given.", args.size()));
                }

                return midi_message::make_note_on(args.at(0), args.at(1), args.at(2));
            }
            else if (type == device_message_type::NOTE_OFF) {
                if (args.size() != 3) {
                    throw std::runtime_error(fmt::format("NOTE_OFF message requires exactly 3 arguments, {} given.", args.size()));
                }

                return midi_message::make_note_on(args.at(0), args.at(1), args.at(2));
            }
            else if (type == device_message_type::SYSEX) {
                if (args.size() < 2) {
                    throw std::runtime_error(fmt::format("MIDI CC message requires at least 2 arguments, {} given.", args.size()));
                }

                return midi_message{ args };
            }

            throw std::out_of_range(fmt::format("Unsupported device message type: {}.", static_cast<int>(type)));
        }
    };
}
