cmake_minimum_required(VERSION 3.26)
project(Project4_starter_files)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(Project4_starter_files
        Invent.h
        main.cpp
        MyString.cpp
        MyString.h
        Project4.cpp)
