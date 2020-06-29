cmake_minimum_required(VERSION 3.14)
project(threads_integration)

set(CMAKE_CXX_STANDARD 14)

add_executable(threads_integration main.cpp)
find_package(Threads REQUIRED)
target_link_libraries(threads_integration Threads::Threads)