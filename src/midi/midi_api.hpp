#pragma once

#include "midi_device.hpp"
#include "midi_port_discovery_result.hpp"
#include <vector>
#include <memory>
#include <optional>

namespace midikeys {
    class midi_api {
    public:
        [[nodiscard]] virtual midi_port_discovery_result discover_ports() const = 0;

        [[nodiscard]] virtual std::unique_ptr<midi_device> make_device(
            const std::string& name,
            const midi_port_descriptor& input_port_descriptor,
            const midi_port_descriptor& output_port_descriptor) const = 0;

        midi_api() = default;

        virtual ~midi_api() = default;

        virtual std::string name() const = 0;
    };
}
