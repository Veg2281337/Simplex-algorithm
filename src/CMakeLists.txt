cmake_minimum_required(VERSION 3.26)
project(simplex_algorithm)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS ON)

include_directories(..)
include_directories(framework)


add_executable(simplex_algorithm application/solver.cpp)
