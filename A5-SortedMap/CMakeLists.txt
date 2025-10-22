cmake_minimum_required(VERSION 3.30)
project(A5_SortedMap)

set(CMAKE_CXX_STANDARD 20)

add_executable(A5_SortedMap main.cpp
        SortedMap.cpp
        SortedMap.h
        SMIterator.cpp
        SMIterator.h
        ShortTest.cpp
        ShortTest.h
        ExtendedTest.cpp
        ExtendedTest.h)
