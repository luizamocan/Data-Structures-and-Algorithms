cmake_minimum_required(VERSION 3.30)
project(A3_IndexedList)

set(CMAKE_CXX_STANDARD 20)

add_executable(A3_IndexedList main.cpp
        ListIterator.cpp
        ListIterator.h
        IndexedList.cpp
        IndexedList.h
        ShortTest.cpp
        ShortTest.h
        ExtendedTest.cpp
        ExtendedTest.h)
