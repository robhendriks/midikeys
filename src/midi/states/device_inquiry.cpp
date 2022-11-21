#include "device_inquiry.hpp"
#include "select_layout.hpp"
#include "forward_input.hpp"
#include <spdlog/spdlog.h>

namespace midikeys::states
{
    device_inquiry::device_inquiry()
        : midikeys::midi_state("device_inquiry")
    {
    }

    void device_inquiry::enter(const midikeys::midi_device& device)
    {
        // Set fixed velocity curve
        device.output().send_message({ 240, 0, 32, 41, 2, 12, 4, 0, 247 });

        // Send inquiry
        device.output().send_message({ 240, 126, 127, 6, 1, 247 });
    }

    void device_inquiry::handle_message(const midikeys::midi_device& device, const midikeys::midi_message& message)
    {
        if (message.starts_with(240) && message.ends_with(247)) {
            if (message.size() >= 10 && message.at(9) == 1) {
                size_t build_number = message.at(12) * 1000 + message.at(13) * 100 + message.at(14) * 10 + message.at(15);
                spdlog::info("Novation Launchpad X, firmware build {}", build_number);

                machine().set_state<select_layout>(device, 1, std::make_unique<forward_input>());
            }
        }
    }

    void device_inquiry::leave(const midikeys::midi_device& device)
    {
    }
}