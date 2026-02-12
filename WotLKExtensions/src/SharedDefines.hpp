#pragma once

#include <Data/DBCAddresses.hpp>
#include <Data/MiscAddresses.hpp>
#include <Data/Enums.hpp>
#include <Data/Math.hpp>
#include <Data/Structs.hpp>

#include <PatchConfig.hpp>
#include <Misc/Util.hpp>

static uint32_t dummy = 0;

static std::unordered_map<char*, void*> luaFuncts;

typedef uint64_t WoWGUID;

// structures
struct CustomNetClient
{
    void* handler[NUM_CUSTOM_MSG_TYPES - SMSG_UPDATE_CUSTOM_COMBAT_RATING];
    void* handlerParam[NUM_CUSTOM_MSG_TYPES - SMSG_UPDATE_CUSTOM_COMBAT_RATING];
};

// Aleist3r: afaik it's not a full structure but I don't need the rest defined
struct WoWTime
{
    int32_t minute;
    int32_t hour;
    int32_t weekDay;
    int32_t monthDay;
    int32_t month;
    int32_t year;
    int32_t flags;
};

struct ZoneLightData
{
    int32_t mapID;
    int32_t lightID;
    void* pointData;
    int32_t pointNum;
    float minX;
    float minY;
    float maxX;
    float maxY;
};

// Client functions
namespace CGChat
{
    CLIENT_FUNCTION(AddChatMessage, 0x509DD0, __cdecl, bool, (char*, uint32_t, uint32_t, uint32_t, uint32_t*, uint32_t, char*, uint64_t, uint32_t, uint64_t, uint32_t, uint32_t, uint32_t*))
}

namespace CGPetInfo
{
    CLIENT_FUNCTION(GetPet, 0x5D3390, __cdecl, WoWGUID, (int32_t))
}

namespace ClientPacket
{
    CLIENT_FUNCTION(MSG_SET_ACTION_BUTTON, 0x5AA390, __cdecl, void, (uint32_t, bool, bool))
}

namespace ClntObjMgr
{
    CLIENT_FUNCTION(GetActivePlayer, 0x4D3790, __cdecl, WoWGUID, ())
    CLIENT_FUNCTION(ObjectPtr, 0x4D4DB0, __cdecl, void*, (WoWGUID, uint32_t))
}

namespace CVar
{
    CLIENT_FUNCTION(sub_766940, 0x766940, __thiscall, void, (void*, int, char, char, char, char))
    CLIENT_FUNCTION(SetCvar, 0x76C9C0, __thiscall, void, (void* cvar, const char* value, bool setDirty, bool, bool, bool forceUpdate))
    CLIENT_FUNCTION(LookupCvar, 0x767460, __cdecl, void*, (const char* name))
}

namespace DNInfo
{
    CLIENT_FUNCTION(AddZoneLight, 0x7ED150, __thiscall, void, (void*, int32_t, float))
    CLIENT_FUNCTION(GetDNInfoPtr, 0x7ECEF0, __stdcall, void*, ())
}

namespace NTempest
{
    CLIENT_FUNCTION(DistanceSquaredFromEdge, 0x7F9C90, __cdecl, bool, (int32_t, void*, C2Vector*, float*))
}

namespace SpellParser
{
    CLIENT_FUNCTION(ParseText, 0x57ABC0, __cdecl, void, (void*, void*, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t))
}

namespace World
{
    CLIENT_FUNCTION(LoadMap, 0x781430, __cdecl, void, (char*, C3Vector*, uint32_t))
    CLIENT_FUNCTION(UnloadMap, 0x783180, __cdecl, void, ())
    CLIENT_FUNCTION(Pos3Dto2D, 0x4F6D20, __fastcall, int, (void* This, void* edx, C3Vector* pos3d, C3Vector* pos2d, uint32_t* flags))
}
