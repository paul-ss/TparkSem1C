cmake_minimum_required(VERSION 3.15)
project(hw_1 C CXX)

set(CMAKE_C_STANDARD 11)
set(CMAKE_C_FLAGS "-Wall -Wextra -Werror")
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wpedantic")
#set(CMAKE_CXX_FLAGS)

find_package(GTest REQUIRED)
find_package(Threads REQUIRED)

include_directories("${GTEST_INCLUDE_DIRS}")
include_directories(project/include)

add_executable(hw_1
        project/src/main.c
        project/src/vector.c
        project/include/vector.h
        project/src/io_data.c
        project/include/io_data.h)


add_executable(
        tests
        tests/test_vector.cpp
        tests/main.cpp
        project/src/vector.c
        project/include/vector.h
        project/src/io_data.c
        project/include/io_data.h tests/test_io_data.cpp)

target_link_libraries(tests ${GTEST_LIBRARIES} Threads::Threads)


enable_testing()
add_test(tests "./tests")