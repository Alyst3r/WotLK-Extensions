#include <Client/DBClient.hpp>

double DBClient::GetGameTableValue(uint32_t tableID, uint32_t classID, uint32_t combatRating)
{
    return reinterpret_cast<double (__cdecl*)(uint32_t, uint32_t, uint32_t)>(0x7F6990)(tableID, classID, combatRating);
}

int32_t DBClient::GetLocalizedRow(void* thisDBC, uint32_t rowIndex, void* row)
{
    return reinterpret_cast<int (__thiscall*)(void*, uint32_t, void*)>(0x4CFD20)(thisDBC, rowIndex, row);
}

void* DBClient::GetRow(void* vtable2, uint32_t rowIndex)
{
    return reinterpret_cast<void* (__thiscall*)(void*, uint32_t)>(0x65C290)(vtable2, rowIndex);
}
