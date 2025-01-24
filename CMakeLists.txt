cmake_minimum_required(VERSION 3.15)
project(BookStore)

set(CMAKE_CXX_STANDARD 20)

add_executable(
    code
    src/MemoryRiver.hpp
    src/FileStore.hpp
    src/read.hpp
    src/main.cpp
)
