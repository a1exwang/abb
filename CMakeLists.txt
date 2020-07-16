cmake_minimum_required(VERSION 3.8)
project(abb)

set(CMAKE_CXX_STANDARD 20)
add_executable(topsort topsort.cpp)
add_executable(concurrent_queue concurrent_queue.cpp)
target_link_libraries(concurrent_queue pthread)