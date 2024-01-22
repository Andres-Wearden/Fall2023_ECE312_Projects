cmake_minimum_required(VERSION 3.26)
project(Project5_starter_files)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(Project5_starter_files
        main.cpp
        Project5.cpp
        Set.h)
