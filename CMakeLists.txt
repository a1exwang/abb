cmake_minimum_required(VERSION 3.8)
project(abb)

set(CMAKE_CXX_STANDARD 20)

add_executable(topsort graph/topsort.cpp)

add_executable(concurrent_queue concurrent_queue.cpp)
target_link_libraries(concurrent_queue pthread)

add_executable(stream_median stream_median.cpp)

add_executable(kmp kmp.cpp)

add_executable(comb comb.cpp)

add_subdirectory(graph)
add_subdirectory(sort)
add_subdirectory(trees)
add_subdirectory(heap)