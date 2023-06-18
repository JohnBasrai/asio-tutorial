include_directories(${CMAKE_CURRENT_SOURCE_DIR})

add_executable(daytime-udp-client       client.cpp)
add_executable(daytime-udp-server-sync  server-sync.cpp)
add_executable(daytime-udp-server-async server-async.cpp)

target_link_libraries(daytime-udp-client       boost_system boost_thread pthread)
target_link_libraries(daytime-udp-server-sync  boost_system boost_thread pthread)
target_link_libraries(daytime-udp-server-async boost_system boost_thread pthread)
