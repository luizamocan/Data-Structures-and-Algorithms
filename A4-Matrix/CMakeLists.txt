cmake_minimum_required(VERSION 3.30)
project(A4_Matrix)

set(CMAKE_CXX_STANDARD 20)

add_executable(A4_Matrix main.cpp
        Matrix.cpp
        Matrix.h
        ShortTest.cpp
        ShortTest.h
        ExtendedTest.cpp
        ExtendedTest.h)
