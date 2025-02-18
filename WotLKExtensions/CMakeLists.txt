# Detours
FetchContent_Declare(
	detours
	GIT_REPOSITORY https://github.com/microsoft/Detours.git
	GIT_TAG v4.0.1
)
FetchContent_MakeAvailable(detours)
FILE(GLOB detours-sources
	${detours_SOURCE_DIR}/src/*.h
	${detours_SOURCE_DIR}/src/*.cpp
)
set_property (
	SOURCE ${detours_SOURCE_DIR}/src/uimports.cpp
	APPEND PROPERTY HEADER_FILE_ONLY true
)
add_library(detours STATIC ${detours-sources})
target_compile_options(detours PRIVATE /W4 /WX /Zi /MT /Gy /Gm- /Zl /Od)
target_include_directories(detours PUBLIC ${detours_SOURCE_DIR})

# Dll
FILE(GLOB WotLKExtensions ${CMAKE_CURRENT_SOURCE_DIR}/*)
SET(WOTLK_EXTENSIONS_H
	Main.h
	Misc.h
	ClientMacros.h
	PatchConfig.h
	Player.h
	SharedDefines.h
	Util.h
	DBCMgr/CustomDBC.h
	DBCMgr/CustomDBCMgr.h
)

SET(WOTLK_EXTENSIONS_CPP
	Main.cpp
	Misc.cpp
	Player.cpp
	Util.cpp
	DBCMgr/CustomDBC.cpp
	DBCMgr/CustomDBCMgr.cpp
)

add_library(WotLKExtensions SHARED
	${WOTLK_EXTENSIONS_H}
	${WOTLK_EXTENSIONS_CPP}
)
set_property(TARGET WotLKExtensions PROPERTY CXX_STANDARD 17)
target_link_libraries(WotLKExtensions detours)

target_include_directories(WotLKExtensions PUBLIC
	${detours_SOURCE_DIR}/src
)

set_property(TARGET WotLKExtensions PROPERTY USE_FOLDERS true)
