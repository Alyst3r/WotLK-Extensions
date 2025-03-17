# Dll
file(GLOB_RECURSE WOTLK_EXTENSIONS_SOURCES CONFIGURE_DEPENDS "*.cpp" "*.h")

add_library(WotLKExtensions SHARED ${WOTLK_EXTENSIONS_SOURCES})
set_property(TARGET WotLKExtensions PROPERTY CXX_STANDARD 17)

set_property(TARGET WotLKExtensions PROPERTY USE_FOLDERS true)

set(LOG_LEVELS DEBUG INFO WARN ERROR NONE)
set(LOG_LEVEL DEBUG CACHE STRING "Logging level")
set_property(CACHE LOG_LEVEL PROPERTY STRINGS ${LOG_LEVELS})

if(LOG_LEVEL STREQUAL "DEBUG")
    target_compile_definitions(WotLKExtensions PRIVATE LOG_LEVEL=4)
elseif(LOG_LEVEL STREQUAL "INFO")
    target_compile_definitions(WotLKExtensions PRIVATE LOG_LEVEL=3)
elseif(LOG_LEVEL STREQUAL "WARN")
    target_compile_definitions(WotLKExtensions PRIVATE LOG_LEVEL=2)
elseif(LOG_LEVEL STREQUAL "ERROR")
    target_compile_definitions(WotLKExtensions PRIVATE LOG_LEVEL=1)
elseif(LOG_LEVEL STREQUAL "NONE")
    target_compile_definitions(WotLKExtensions PRIVATE LOG_LEVEL=0)
else()
    message(FATAL_ERROR "Invalid LOG_LEVEL ${LOG_LEVEL}")
endif()

