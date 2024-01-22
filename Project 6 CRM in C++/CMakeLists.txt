cmake_minimum_required(VERSION 3.26)
project(Project7_starter_files)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)
include_directories(__MACOSX)

add_executable(Project7_starter_files
        Customer.h
        cmake-build-debug/.cmake/CustomerDB.cpp
        CustomerDB.h
        main.cpp
        Project7.cpp
        UTString.h)
