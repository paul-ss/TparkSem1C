cmake_minimum_required(VERSION 3.15)
project(hw_2)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_C_STANDARD 11)
set(CMAKE_C_FLAGS "-pthread")

include_directories(project/include)

add_executable(hw-2
        project/include/matrix.h
        project/src/main.c
        project/src/matrix.c project/src/matrix_optimised.c project/include/matrix_optimised.h project/src/array.c project/include/array.h)

add_executable(gen
        gen_data/gen.cpp)