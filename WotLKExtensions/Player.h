#pragma once

#include "SharedDefines.h"

class Player
{
public:
	static void ApplyPatches();
private:
	static inline uint32_t memoryTable[64] = { 0 };
	static inline uint32_t raceNameTable[32] = { 0 };
	static void CharacterCreationRaceCrashfix();
};
