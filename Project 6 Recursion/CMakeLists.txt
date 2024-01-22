cmake_minimum_required(VERSION 3.26)
project(Project6_starter_files)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(Project6_starter_files
        main.cpp
        MazeParams.h
        Project6.cpp
        Recursion.h)
