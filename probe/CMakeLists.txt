add_executable (midiprobe main.cpp)

set_property(TARGET midiprobe PROPERTY CXX_STANDARD 20)

target_link_libraries(midiprobe rtmidi)
