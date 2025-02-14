#pragma once

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
// Enables custom DBC manager
static bool useCustomDBCs = false;
