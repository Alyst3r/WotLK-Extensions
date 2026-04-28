# Dll
cmake_minimum_required(VERSION 3.25)

set(CMAKE_GENERATOR_PLATFORM Win32)

set(CMAKE_CXX_STANDARD 17)

set(CMAKE_INTERPROCEDURAL_OPTIMIZATION TRUE)

project(WotlkExtensions LANGUAGES CXX)

option(CUSTOM_DBC "Enable custom DBC loader" OFF)
option(LFGROLES_DBC "Dungeon finder roles dehardcoded to custom DBC file; requires custom DBC loader" OFF)
option(ZONELIGHT_DBC "Enables ZoneLight.cdbc as seen in newer expansions; requires custom DBC loader" OFF)
option(NOAMMO_PATCH "Removes need for ammo for ranged weapons" OFF)
option(CHARCREATIONRACE_FIX "Fixes crash if more than 21 playable races are present during character creation" ON)
option(COMBOPOINT_FIX "Fix for combo points so they work for all classes" ON)
option(CLASSLFDROLES_PATCH "Allow more than 12 classes in dungeon finder" ON)
option(OOBLUAFUNCTIONS_PATCH "Allows registering lua functions from addresses outside of wow.exe; suggested to leave it on as it's required for various other patches" ON)
option(CUSTOMPACKETS_PATCH "Enables possibility of implementing and using custom packets" OFF)
option(ITEMMODEXT_PATCH "Expands ITEM_MOD table, allowing to add and display more custom tooltip mods - see Misc.hpp for more info" OFF)
option(SPELLDESCRIPTIONEXT_PATCH "Enables possibility to add more variable arguments used in spell descriptions, like $hp, $ power1, etc." OFF)
option(ACTIONBAR_LUA "Enables some additional action bar functions like 'ReplaceActionBarSpell'" OFF)
option(DEVHELPER_LUA "Various Lua functions useful in dev, like 'ReloadMap' or toggle rendering of various elements: liquids, terrain, etc." OFF)
option(TOOLTIPID_PATCH "Enables ID display of various targeted elements, such as spells, items or npcs in tooltip. Work in progress." OFF)
option(TOOLTIPDKRUNEEXT_PATCH "Enables possibility to display runic power cost next to rune cost. Requires some core edits. More info in 'CGTooltip::AppendRuneCostLine' function." OFF)
option(SPELLATTRIBUTESEXTENDED_DBC "Enables additional (mostly client-side) spell attributes that could, for example, be used to modify behavior of various part of tooltip; requires custom DBC loader" OFF)
option(GLUEMGREXTENSION "Extends GlueMgr, allowing to register new CVars and Lua functions (for login/character selection screens)" OFF)
option(OCCLUSIONVOLUME_DBC "Enables OcclusionVolume.cdbc, dehardcoding occluders used in various places, for example between Stormwind and Elwynn; requires custom DBC loader" OFF)

configure_file(
    "${CMAKE_CURRENT_SOURCE_DIR}/cmake/PatchConfig.hpp.in"
    "${CMAKE_CURRENT_SOURCE_DIR}/include/PatchConfig.hpp"
)

file(GLOB_RECURSE WotlkExt_sources CONFIGURE_DEPENDS
    "${CMAKE_CURRENT_SOURCE_DIR}/src/*.c"
    "${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp"
)

file(GLOB_RECURSE WotlkExt_includes CONFIGURE_DEPENDS
    "${CMAKE_CURRENT_SOURCE_DIR}/src/*.h"
    "${CMAKE_CURRENT_SOURCE_DIR}/src/*.hpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/src/*.inl"
)

add_library(WotLKExtensions SHARED
    ${WotlkExt_sources}
)

target_sources(WotLKExtensions PRIVATE
    FILE_SET HEADERS
    BASE_DIRS ${CMAKE_CURRENT_SOURCE_DIR}/src
    FILES ${WotlkExt_includes}
)

if(MSVC)
    target_compile_definitions(WotLKExtensions PUBLIC _CRT_SECURE_NO_WARNINGS)
endif()

target_include_directories(WotLKExtensions PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/include/
    ${CMAKE_CURRENT_SOURCE_DIR}/src/
)
source_group(TREE "${CMAKE_CURRENT_SOURCE_DIR}/src" PREFIX "DLL" FILES
    ${WotlkExt_sources}
    ${WotlkExt_includes}
)
