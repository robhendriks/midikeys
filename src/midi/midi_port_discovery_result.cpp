#include "midi_port_discovery_result.hpp"

namespace midikeys {
    static std::optional<midi_port_descriptor>
    find(const std::vector<midi_port_descriptor> &ports, const size_t port_number) {
        const auto it = std::find_if(ports.begin(), ports.end(),
                                     [&port_number](const midi_port_descriptor &port_descriptor) {
                                         return port_descriptor.port_number == port_number;
                                     });

        if (it != ports.end()) {
            return *it;
        }

        return std::nullopt;
    }

    std::optional<midi_port_descriptor> midi_port_discovery_result::find_input(const size_t port_number) const {
        return find(inputs, port_number);
    }

    std::optional<midi_port_descriptor> midi_port_discovery_result::find_output(const size_t port_number) const {
        return find(outputs, port_number);
    }
}