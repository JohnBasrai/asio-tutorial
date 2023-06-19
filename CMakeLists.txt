cmake_minimum_required(VERSION 3.18.0)
project (ASIO-TUTORIAL)

include(${ASIO-TUTORIAL_BINARY_DIR}/conanbuildinfo.cmake)
conan_basic_setup()

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++17")

add_subdirectory(daytime-iostreams)
add_subdirectory(daytime-tcp)
add_subdirectory(daytime-udp)
add_subdirectory(dummy-work)
add_subdirectory(read-udp)
add_subdirectory(signals)
add_subdirectory(timers)
