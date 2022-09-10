cmake_minimum_required(VERSION 3.20)
project(NetFramework)

set(CMAKE_CXX_STANDARD 20)
#add_subdirectory(lib/asio EXCLUDE_FROM_ALL)

add_library(NetFramework INTERFACE)
target_include_directories(NetFramework INTERFACE include/)

#target_link_libraries(netframework INTERFACE asio)