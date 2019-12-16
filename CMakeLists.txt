cmake_minimum_required(VERSION 3.15)
project(TreeBuilder9001)

set(CMAKE_CXX_STANDARD 14)

include_directories(src)

add_executable(TreeBuilder9001
        src/Tree.h
        src/TreeBuilder.cpp
        src/TreeImplementation.cpp
        test/main.cpp)
