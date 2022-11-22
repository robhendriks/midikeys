include(FetchContent)

FetchContent_Declare(
  yaml-cpp
  GIT_REPOSITORY https://github.com/jbeder/yaml-cpp.git
  GIT_TAG yaml-cpp-0.7.0
)

option(YAML_BUILD_SHARED_LIBS "" OFF)

FetchContent_MakeAvailable(yaml-cpp)
