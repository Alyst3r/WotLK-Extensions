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

uint32_t ClientServices::GetPowerDivisor(int32_t powerType)
{
    switch (powerType)
    {
        case 1:
        case 6:
            return 10;
        case 4:
            return 1000;
        case 0:
        case 2:
        case 3:
        case 5:
        default:
            return 1;
    }
}

CGUnit* ClientServices::GetUnitFromName(const char* name)
{
    return reinterpret_cast<CGUnit* (__cdecl*)(const char*)>(0x60C1F0)(name);
}

void ClientServices::InitializePlayer()
{
    reinterpret_cast<void (__cdecl*)()>(0x6E83B0)();
}

void ClientServices::SendPacket(CDataStore* packet)
{
    reinterpret_cast<void (__cdecl*)(CDataStore*)>(0x6B0B50)(packet);
}

SkillLineAbilityRow* ClientServices::SpellTableLookupAbility(uint32_t raceID, uint32_t classID, int32_t spellID)
{
    return reinterpret_cast<SkillLineAbilityRow* (__cdecl*)(uint32_t, uint32_t, uint32_t)>(0x812410)(raceID, classID, spellID);
}
