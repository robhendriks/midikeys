include(FetchContent)

FetchContent_Declare(
  spdlog
  GIT_REPOSITORY https://github.com/gabime/spdlog.git
  GIT_TAG v1.11.0
)

option(BUILD_SHARED_LIBS "" FALSE)

FetchContent_MakeAvailable(spdlog)
