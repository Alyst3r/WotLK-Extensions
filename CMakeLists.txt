cmake_minimum_required(VERSION 3.22)
Include(FetchContent)
set(CMAKE_GENERATOR_PLATFORM Win32)
cmake_policy(SET CMP0048 NEW)

project(WotLKExtensions)

add_subdirectory(Patcher)
add_subdirectory(WotLKExtensions)
