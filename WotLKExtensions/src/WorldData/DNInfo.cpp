#include <WorldData/DNInfo.hpp>

void DNInfo::AddZoneLight(void* thisDNInfo, int32_t lightId, float f)
{
    reinterpret_cast<void (__thiscall*)(void*, int32_t, float)>(0x7ED150)(thisDNInfo, lightId, f);
}

void* DNInfo::GetDNInfoPtr()
{
    return reinterpret_cast<void* (__stdcall*)()>(0x7ECEF0)();
}
