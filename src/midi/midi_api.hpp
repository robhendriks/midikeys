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
    };
}