#include <Client/CGReputationInfo.hpp>

int32_t CGReputationInfo::GetFactionStanding(int32_t faction)
{
    return reinterpret_cast<int32_t (__cdecl*)(int32_t)>(0x5D05B0)(faction);
}
