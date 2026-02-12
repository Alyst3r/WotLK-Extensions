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
};
