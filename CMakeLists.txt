cmake_minimum_required(VERSION 3.0)

set(CMAKE_CXX_FLAGS "-Wall -std=c++14")
set(CMAKE_CXX_FLAGS_DEBUG "-g")
set(CMAKE_CXX_FLAGS_RELEASE "-O2")

if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE "Debug")
endif(NOT CMAKE_BUILD_TYPE)

message(STATUS "Build Type: ${CMAKE_BUILD_TYPE}")

include_directories(${PROJECT_SOURCE_DIR}/logger)
aux_source_directory(${PROJECT_SOURCE_DIR}/test TEST_SRC)

add_executable(log_test ${TEST_SRC})

