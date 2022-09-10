cmake_minimum_required(VERSION 3.20)
set(CMAKE_CXX_STANDARD 20)

add_executable(Playground main.cpp)

target_link_libraries(Playground NetFramework)