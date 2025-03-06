#include "SharedDefines.h"

class Misc
{
public:
	static void ApplyPatches();

	static void SetYearOffsetMultiplier();
private:
	// defaults: 49 and 37 - both need to be increased by number of mods you add
	// itemModTableVal is capped on 127 until I rewrite some parts of the code - if I do that is
	// so and so itemModTable is capped to 139 I think :P
	static inline uint32_t itemModTable[49] = { 0 };
	static inline uint32_t itemModTableVal[37] = { 0 };

	static inline uint32_t yearOffsetMult = 0;

	static char* GetTimeString(WoWTime* a1, char* a2, uint32_t a3);
	static void PackTimeDataToDword(uint32_t* packedTime, uint32_t minute, uint32_t hour, uint32_t weekDay, uint32_t monthDay, uint32_t month, uint32_t year, uint32_t flags);
	static void PackWoWTimeToDword(uint32_t* dword, WoWTime* time);
	static void UnpackWoWTime(uint32_t packedTime, uint32_t* minute, uint32_t* hour, uint32_t* weekDay, uint32_t* monthDay, uint32_t* month, uint32_t* year, uint32_t* flags);
};
