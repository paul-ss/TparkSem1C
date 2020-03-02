cmake_minimum_required(VERSION 3.15)
project(hw_1 C)

set(CMAKE_C_STANDARD 99)

include_directories(include)

add_executable(hw_1 src/main.c src/vector.c include/vector.h src/io_data.c include/io_data.h)