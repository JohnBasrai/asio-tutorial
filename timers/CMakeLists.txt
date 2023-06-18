include_directories(${CMAKE_CURRENT_SOURCE_DIR})

set(prog1 "timer1")
add_executable(${prog1} ${prog1}.cpp)
target_link_libraries(${prog1} boost_system boost_thread pthread)

set(prog2 "timer2")
add_executable(${prog2} ${prog2}.cpp)
target_link_libraries(${prog2} boost_system boost_thread pthread)

set(prog3 "timer3")
add_executable(${prog3} ${prog3}.cpp)
target_link_libraries(${prog3} boost_system boost_thread pthread)

set(prog4 "timer4")
add_executable(${prog4} ${prog4}.cpp)
target_link_libraries(${prog4} boost_system boost_thread pthread)

set(prog5 "timer5")
add_executable(${prog5} ${prog5}.cpp)
target_link_libraries(${prog5} boost_system boost_thread pthread)

