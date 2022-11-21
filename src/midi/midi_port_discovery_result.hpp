#pragma once

#include <vector>
#include <optional>
#include "midi_port.hpp"

namespace midikeys {
    struct midi_port_discovery_result {
        const std::vector<midi_port_descriptor> inputs;
        const std::vector<midi_port_descriptor> outputs;

        [[nodiscard]] std::optional<midi_port_descriptor> find_input(const size_t port_number) const;

        [[nodiscard]] std::optional<midi_port_descriptor> find_output(const size_t port_number) const;
    };
}