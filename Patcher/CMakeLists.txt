FILE(GLOB patcher-sources ${CMAKE_CURRENT_SOURCE_DIR}/*)
add_executable(Patcher ${patcher-sources})
set_property(TARGET Patcher PROPERTY CXX_STANDARD 17)
