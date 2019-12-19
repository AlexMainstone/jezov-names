cmake_minimum_required(VERSION 3.0.0)
project(jezov)

list(APPEND SOURCES
    "${CMAKE_SOURCE_DIR}/test/Main.cpp"
    "${CMAKE_SOURCE_DIR}/include/Markov.hpp"
)

add_executable(jezov ${SOURCES})