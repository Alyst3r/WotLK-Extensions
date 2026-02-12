#include <GameObjects/CGPetInfo.hpp>

WoWGUID CGPetInfo::GetPet(int32_t index)
{
    return reinterpret_cast <WoWGUID (__cdecl*)(int32_t)>(0x5D3390)(index);
}
