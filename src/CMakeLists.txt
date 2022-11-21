file(GLOB_RECURSE SOURCES *.cpp)
file(GLOB_RECURSE HEADERS *.hpp)

add_executable (midikeys ${SOURCES} ${HEADERS})

target_compile_definitions(midikeys PRIVATE USE_RTMIDI_API=1)

set_property(TARGET midikeys PROPERTY CXX_STANDARD 20)

target_link_libraries(midikeys argh rtmidi spdlog_header_only tomlplusplus::tomlplusplus)

add_custom_target(copy_resources ALL
        COMMAND ${CMAKE_COMMAND} -E copy_directory
        ${PROJECT_SOURCE_DIR}/resources
        ${CMAKE_CURRENT_BINARY_DIR})

add_dependencies(midikeys copy_resources)