#include <Client/ClientServices.hpp>

WoWGUID ClientServices::GetActivePlayer()
{
    return reinterpret_cast<WoWGUID (__cdecl*)()>(0x4D3790)();
}

uint8_t ClientServices::GetCharacterClass()
{
    return reinterpret_cast<uint8_t (__cdecl*)()>(0x6B1080)();
}

void* ClientServices::GetObjectPtr(WoWGUID objGUID, uint32_t typeMask)
{
    return reinterpret_cast<void* (__cdecl*)(WoWGUID, uint32_t)>(0x4D4DB0)(objGUID, typeMask);
}

void ClientServices::InitializePlayer()
{
    reinterpret_cast<void (__cdecl*)()>(0x6E83B0)();
}

void ClientServices::SendPacket(CDataStore* packet)
{
    reinterpret_cast<void (__cdecl*)(CDataStore*)>(0x6B0B50)(packet);
}
