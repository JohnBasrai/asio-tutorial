include_directories(${CMAKE_CURRENT_SOURCE_DIR})

set(prog1 "signal")

add_executable(${prog1} ${prog1}.cpp)

target_link_libraries(${prog1} boost_system boost_thread pthread)

