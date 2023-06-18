include_directories(${CMAKE_CURRENT_SOURCE_DIR})

add_executable(daytime-tcp-client client.cpp)
add_executable(daytime-tcp-server-sync server-sync.cpp)
add_executable(daytime-tcp-server-async server-async.cpp)

target_link_libraries(daytime-tcp-client boost_system boost_thread pthread)
target_link_libraries(daytime-tcp-server-sync boost_system boost_thread pthread)
target_link_libraries(daytime-tcp-server-async boost_system boost_thread pthread)
