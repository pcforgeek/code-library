cmake_minimum_required(VERSION 3.10)
project(code-library)

set(PROJECT_INCLUDE_DIR ${PROJECT_SOURCE_DIR}/include)

include_directories("${PROJECT_SOURCE_DIR}")
include_directories("${PROJECT_INCLUDE_DIR}")
include_directories("${PROJECT_SOURCE_DIR}/src")
set(CMAKE_CXX_STANDARD 11)


add_executable(code-library
        include/algorithm_driver.h
        include/dynamic_programming_driver.h
        include/data_structure_driver.h
        include/algorithms.h
        include/data_structure.h
        include/dynamic_programming.h
        )
