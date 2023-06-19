include_directories(${CMAKE_CURRENT_SOURCE_DIR})

add_executable(daytime-iostreams-client client.cpp)
add_executable(daytime-iostreams-server server.cpp)

target_link_libraries(daytime-iostreams-client boost_system boost_thread pthread)
target_link_libraries(daytime-iostreams-server boost_system boost_thread pthread)
