cmake_minimum_required(VERSION 3.26)
project(MatrixProject)

set(CMAKE_CXX_STANDARD 20)

add_executable(MatrixProject main.cpp
        Matrix.cpp
        Matrix.hpp
        Timer.cpp
        Timer.hpp)
