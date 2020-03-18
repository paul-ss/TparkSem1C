cmake_minimum_required(VERSION 3.12)
project(hw_2)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_C_STANDARD 11)

set(CMAKE_C_FLAGS "-pthread  -fopenmp")
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall -Werror -Wpedantic")
set(CMAKE_CXX_FLAGS "-pthread")

if ($ENV{COVERAGE})
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} --coverage")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} --coverage")
    message("-- Coverage enable")
else ()
    message("-- Coverage disable")
endif()


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
        project/src/matrix_optimised.c
        project/src/array_optimised.c
        project/include/array_optimised.h)


add_executable(gen
        gen_data/main.cpp)

add_executable(hw2_naive
        project/src/main.c)

add_executable(hw2_opt
        project/src/main.c)

add_executable(tests_naive
        tests/main.cpp
        tests/test_matrix.cpp
        tests/utils.cpp
        tests/utils.h)

add_executable(tests_opt
        tests/main.cpp
        tests/test_matrix.cpp
        tests/utils.cpp
        tests/utils.h)

target_link_libraries(hw2_naive matrix_naive)
target_link_libraries(hw2_opt matrix_opt)
target_link_libraries(tests_naive ${GTEST_LIBRARIES} matrix_naive)
target_link_libraries(tests_opt ${GTEST_LIBRARIES} Threads::Threads matrix_opt)


enable_testing()
add_test(tests_naive "./tests")
add_test(tests_opt "./tests")
