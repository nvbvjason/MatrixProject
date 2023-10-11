cmake_minimum_required(VERSION 3.26)
project(MatrixProject)

set(CMAKE_CXX_STANDARD 17)

add_executable(MatrixProject main.cpp
        Matrix.cpp
        Matrix.hpp)
