cmake_minimum_required(VERSION 3.25)

set(CMAKE_GENERATOR_PLATFORM Win32)

cmake_policy(SET CMP0048 NEW)

project(WotLKExtensions)

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

add_subdirectory(Patcher)
add_subdirectory(WotLKExtensions)
