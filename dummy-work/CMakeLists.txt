include_directories(${CMAKE_CURRENT_SOURCE_DIR})

set(prog "dummy-work")

add_executable(${prog} ${prog}.cpp)

target_link_libraries(${prog} boost_system boost_thread pthread)

