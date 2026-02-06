#include <SharedDefines.hpp>

class Misc
{
public:
    static void ApplyPatches();

    static void SetYearOffsetMultiplier();
private:
    Misc() = delete;
    ~Misc() = delete;

    // defaults: 49 and 37 - both need to be increased by number of mods you add
    // itemModTableVal is capped on 127 until I rewrite some parts of the code - if I do that is
    // so and so itemModTable is capped to 139 I think :P
    static inline uint32_t itemModTable[49] = { 0 };
    static inline uint32_t itemModTableVal[37] = { 0 };

    static inline uint32_t yearOffsetMult = 0;

    static void ApplyWoWTimePatches();
    static char* GetTimeString(WoWTime* a1, char* a2, uint32_t a3);
    static void PackTimeDataToDword(uint32_t* packedTime, int32_t minute, int32_t hour, int32_t weekDay, int32_t monthDay, int32_t month, int32_t year, int32_t flags);
    static void PackWoWTimeToDword(uint32_t* dword, WoWTime* time);
    static void UnpackWoWTime(uint32_t packedTime, int32_t* minute, int32_t* hour, int32_t* weekDay, int32_t* monthDay, int32_t* month, int32_t* year, int32_t* flags);
};
