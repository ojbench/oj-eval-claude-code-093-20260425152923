cmake_minimum_required(VERSION 3.10)
project(problem_093 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Ensure the produced binary is named exactly 'code' and ends up in repo root
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR})

add_executable(code code.cpp)

target_compile_options(code PRIVATE -O2 -pipe -Wall -Wextra -Wshadow -Wconversion -Wno-sign-conversion)
