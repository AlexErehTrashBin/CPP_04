cmake_minimum_required(VERSION 3.28)
project(CPP_04)

set(CMAKE_CXX_STANDARD 17)

add_executable(CPP_04 src/main.cpp
        src/employee.h
        src/stdafx.h
        src/input_utils.h
        src/main.h)
