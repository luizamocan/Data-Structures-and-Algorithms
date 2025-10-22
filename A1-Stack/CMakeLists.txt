cmake_minimum_required(VERSION 3.30)
project(A1_Stack)

set(CMAKE_CXX_STANDARD 20)

add_executable(A1_Stack main.cpp
        Stack.cpp
        Stack.h
        ShortTest.cpp
        ShortTest.h
        ExtendedTest.cpp
        ExtendedTest.h)
