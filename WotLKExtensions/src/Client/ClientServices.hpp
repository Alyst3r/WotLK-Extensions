#pragma once

#include <Data/Structs.hpp>
#include <GameObjects/CGUnit.hpp>

#include <SharedDefines.hpp>

#include <cstdint>

struct CDataStore;

class ClientServices
{
public:
    static uint8_t __fastcall CharacterLogoutEx(void* thisChar, uint32_t unused, char a2, uint8_t a3);
    static WoWGUID GetActivePlayer();
    static uint8_t GetCharacterClass();
    static void* GetObjectPtr(WoWGUID objGUID, uint32_t typeMask);
    static uint32_t GetPowerDivisor(int32_t powerType);
    static CGUnit* GetUnitFromName(const char* name);
    static void InitializePlayer();
    static void SendPacket(CDataStore* packet);
    static SkillLineAbilityRow* SpellTableLookupAbility(uint32_t raceID, uint32_t classID, int32_t spellID);

private:
    ClientServices() = delete;
    ~ClientServices() = delete;
};
