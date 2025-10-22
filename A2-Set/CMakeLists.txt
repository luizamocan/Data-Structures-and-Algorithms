cmake_minimum_required(VERSION 3.30)
project(A2_Set)

set(CMAKE_CXX_STANDARD 20)

add_executable(A2_Set main.cpp
        Set.cpp
        Set.h
        SetIterator.cpp
        SetIterator.h
        ShortTest.cpp
        ShortTest.h
        ExtendedTest.cpp
        ExtendedTest.h)
