cmake_minimum_required(VERSION 3.20)
project(NetFramework)

set(CMAKE_CXX_STANDARD 20)

add_compile_definitions(ASIO_STANDALONE)
add_library(NetFramework INTERFACE)
target_include_directories(NetFramework INTERFACE include lib/asio/asio/include)
target_link_libraries(NetFramework INTERFACE ws2_32)
