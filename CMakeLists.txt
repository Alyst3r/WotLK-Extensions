cmake_minimum_required(VERSION 3.25)

set(CMAKE_GENERATOR_PLATFORM Win32)

cmake_policy(SET CMP0048 NEW)

project(WotLKExtensions)

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

add_subdirectory(Patcher)
add_subdirectory(WotLKExtensions)

set(CLIENT_PATH "" CACHE PATH "Path to your WoW client")

add_custom_target(
    copy_files ALL
    COMMAND ${CMAKE_COMMAND} -E copy_directory
    "${CMAKE_BINARY_DIR}/bin/$<CONFIG>"
    "${CLIENT_PATH}"
)

if(NOT CLIENT_PATH STREQUAL "")
	add_dependencies(
	    copy_files
        Patcher
        WotLKExtensions
    )
	message("Patcher.exe and WotLKExtensions.dll will be written to ${CLIENT_PATH} on build.")
    file(WRITE "${CLIENT_PATH}/Patcher.bat"
	    "@echo off\n"
		"patcher.exe wow.exe\n"
		"pause\n"
    )
    message("Patcher.bat created in ${CLIENT_PATH}. You may run it to auto-patch Wow.exe after project build.")
endif()
