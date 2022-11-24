cmake_minimum_required(VERSION 3.20 FATAL_ERROR)

project(midikeys)

set(BUILD_PROBE OFF CACHE BOOL "Build probe tool?")

add_subdirectory(3rd_party)

file(GLOB_RECURSE SOURCES src/*.cpp)
file(GLOB_RECURSE HEADERS src/*.hpp)

add_executable(midikeys ${SOURCES} ${HEADERS})

target_compile_definitions(midikeys PRIVATE USE_RTMIDI_API=1)

set_property(TARGET midikeys PROPERTY CXX_STANDARD 20)

if (APPLE)
    target_link_libraries(midikeys argh rtmidi spdlog_header_only yaml-cpp "-framework Cocoa" "-framework ApplicationServices")
else()
    target_link_libraries(midikeys argh rtmidi spdlog_header_only yaml-cpp)
endif()

add_custom_target(copy_resources ALL
        COMMAND ${CMAKE_COMMAND} -E copy_directory
        ${PROJECT_SOURCE_DIR}/resources
        ${CMAKE_CURRENT_BINARY_DIR})

add_dependencies(midikeys copy_resources)
