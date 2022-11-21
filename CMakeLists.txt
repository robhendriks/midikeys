cmake_minimum_required(VERSION 3.20 FATAL_ERROR)

project(midikeys)

set(BUILD_PROBE OFF CACHE BOOL "Build probe tool?")

add_subdirectory(3rd_party)
add_subdirectory(src)

if (BUILD_PROBE)
    add_subdirectory(probe)
endif()
