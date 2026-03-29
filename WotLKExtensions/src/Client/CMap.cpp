#include <Client/CMap.hpp>
#include <Client/SFile.hpp>
#include <Misc/Util.hpp>

void CMap::Apply()
{
    Util::OverwriteUInt32AtAddress(0x7D7162, reinterpret_cast<uint32_t>(&SafeOpenEx) - 0x7D7166);
    Util::OverwriteUInt32AtAddress(0x7D80E9, reinterpret_cast<uint32_t>(&SafeOpenEx) - 0x7D80ED);
    Util::OverwriteUInt32AtAddress(0x7D8100, reinterpret_cast<uint32_t>(&SafeOpenEx) - 0x7D8104);
    Util::OverwriteUInt32AtAddress(0x7D8670, reinterpret_cast<uint32_t>(&SafeOpenEx) - 0x7D8674);
}

bool CMap::SafeOpenEx(const char* filename, HANDLE* a2)
{
    for (int i = 0; i < 10; i++)
        if (SFile::OpenFile(filename, a2))
            return true;

    return SFile::OpenFile("Spells\\ErrorCube.mdx", a2);
}
