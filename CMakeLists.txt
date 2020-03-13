cmake_minimum_required(VERSION 3.12)
project(hw_2)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_C_STANDARD 11)

set(CMAKE_C_FLAGS "-pthread  -fopenmp")
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall -Werror -Wpedantic --coverage")
set(CMAKE_CXX_FLAGS "--coverage")

find_package(GTest REQUIRED)
find_package(Threads REQUIRED)

include_directories("${GTEST_INCLUDE_DIRS}")
include_directories(project/include)

add_library(matrix_naive STATIC
        project/src/matrix.c
        project/src/array.c
        project/include/matrix.h
        project/include/array.h
        project/src/matrix_naive.c)

add_library(matrix_opt SHARED
        project/src/matrix.c
        project/src/array.c
        project/include/matrix.h
        project/include/array.h
        project/src/matrix_optimised.c)


add_executable(gen
        gen_data/main.cpp)

add_executable(hw2_naive
        project/src/main.c)

add_executable(hw2_opt
        project/src/main.c)

add_executable(tests
        tests/main.cpp
        tests/test_matrix.cpp tests/utils.cpp tests/utils.h)

target_link_libraries(hw2_naive matrix_naive)
target_link_libraries(hw2_opt matrix_opt)
target_link_libraries(tests ${GTEST_LIBRARIES} Threads::Threads matrix_naive)


enable_testing()
add_test(tests "./tests")
