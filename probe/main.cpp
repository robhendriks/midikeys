#include <RtMidi.h>
#include <iostream>

static void list_ports(RtMidi* midi)
{
    const size_t nPorts = midi->getPortCount();

    for (size_t i = 0; i < nPorts; ++i) {
        std::cout << "Port " << i << midi->getPortName(i) << std::endl;
    }
}

int main(const int argc, const char* argv[])
{
    RtMidiIn in;
    RtMidiOut out;

    std::cout << "Inputs:" << std::endl;
    list_ports(&in);
    std::cout << "Outputs:" << std::endl;
    list_ports(&out);

    return 0;
}