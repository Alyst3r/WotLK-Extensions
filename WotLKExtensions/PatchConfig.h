#pragma once

// Custom DBC Mgr
static bool useCustomDBCFiles = false;
// roles dbc
static bool useLFGRolesDBC = false;

// Patches
// Makes ranged weapons require no ammo; requires some core changes to fix visuals
static bool noAmmoPatch = false;
// Fix for more than 21 races crash in character creation
static bool characterCreationRaceFix = false;
// Fix combo points so they work for all classes
static bool comboPointFix = false;
// Allow more than 12 classes in dungeon finder and shizz
static bool classLFDRoles = false;
// Allow registering custom Lua functions from outside of wow.exe
static bool outOfBoundLuaFunctions = false;
// Use custom packets
static bool customPackets = false;
// expands ITEM_MOD table, allowing to add and display more custom tooltip mods
// see Misc.h if you set it to true
// unlocks certain custom lua functions
static bool extendedItemMods = false;

// Lua functions
// Action bar slot functions
static bool customActionBarFunctions = false;
// Various dev functions
static bool devHelperFunctions = false;
