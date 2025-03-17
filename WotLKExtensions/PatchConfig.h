#pragma once

// Custom DBC Mgr
static bool useCustomDBCFiles = true;
// roles dbc
static bool useLFGRolesDBC = true;

// Patches
// Makes ranged weapons require no ammo; requires some core changes to fix visuals
static bool noAmmoPatch = true;
// Fix for more than 21 races crash in character creation
static bool characterCreationRaceFix = true;
// Fix combo points so they work for all classes
static bool comboPointFix = true;
// Allow more than 12 classes in dungeon finder and shizz
static bool classLFDRoles = true;
// Allow registering custom Lua functions from outside of wow.exe
static bool outOfBoundLuaFunctions = true;
// Use custom packets
static bool customPackets = true;
// expands ITEM_MOD table, allowing to add and display more custom tooltip mods
// see Misc.h if you set it to true
// unlocks certain custom lua functions
static bool extendedItemMods = true;

// Lua functions
// Action bar slot functions
static bool customActionBarFunctions = true;
// Various dev functions
static bool devHelperFunctions = true;
