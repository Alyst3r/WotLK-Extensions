#pragma once

#include <Data/Structs.hpp>

#include <SharedDefines.hpp>

#include <cstdint>

struct CDataStore;

class ClientServices
{
public:
    static WoWGUID GetActivePlayer();
    static uint8_t GetCharacterClass();
    static void* GetObjectPtr(WoWGUID objGUID, uint32_t typeMask);
    static void InitializePlayer();
    static void SendPacket(CDataStore* packet);
    static SkillLineAbilityRow* SpellTableLookupAbility(uint32_t raceID, uint32_t classID, uint32_t spellID);

private:
    ClientServices() = delete;
    ~ClientServices() = delete;
};
