include(FetchContent)

FetchContent_Declare(
  rtmidi
  GIT_REPOSITORY https://github.com/thestk/rtmidi.git
  GIT_TAG 5.0.0
)

option(RTMIDI_BUILD_STATIC_LIBS "" ON)
option(RTMIDI_BUILD_TESTING "" OFF)

FetchContent_MakeAvailable(rtmidi)
