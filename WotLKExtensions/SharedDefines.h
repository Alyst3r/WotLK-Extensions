#pragma once

#include "PatchConfig.h"
#include "Util.h"

struct lua_State;

static uint32_t dummy = 0;

static std::unordered_map<char*, void*> luaFuncts;

// structures
struct C3Vector
{
	float x;
	float y;
	float z;
};

struct CMovement
{
	uint32_t padding0x00[4];
	C3Vector position;
	float padding0x1C;
	float orientation;
	float pitch;
	uint32_t padding28[7];
	uint32_t movementFlags;
	uint32_t movementFlags2;
	uint32_t padding0x4C[63];
};

struct CGUnit
{
	uint32_t padding0x00[54];
	CMovement* movementInfo;
	uint32_t padding0x34[971];
};

struct MapRow
{
	uint32_t m_ID;
	char* m_Directory;
	uint32_t padding0x08[17];
};

struct SpellRow
{
	uint32_t m_ID;
	uint32_t padding0x04[135];
	char* m_name_lang;
	char* m_nameSubtext_lang;
	char* m_description_lang;
	char* m_auraDescription_lang;
	uint32_t padding0x230[30];
};

// Client functions
namespace CGUnit_C
{
	CLIENT_FUNCTION(GetShapeshiftFormId, 0x71AF70, __thiscall, uint32_t, (CGUnit*))
}

namespace ClientDB
{
	CLIENT_FUNCTION(GetLocalizedRow, 0x4CFD20, __thiscall, int, (void*, uint32_t, void*))
	CLIENT_FUNCTION(GetRow, 0x65C290, __thiscall, void*, (void*, uint32_t))
}

namespace ClientPacket
{
	CLIENT_FUNCTION(MSG_SET_ACTION_BUTTON, 0x5AA390, __cdecl, void, (uint32_t, bool, bool))
}

namespace ClntObjMgr {
	CLIENT_FUNCTION(GetActivePlayer, 0x4D3790, __cdecl, uint64_t, ())
	CLIENT_FUNCTION(ObjectPtr, 0x4D4DB0, __cdecl, void*, (uint64_t, uint32_t))
}

namespace FrameScript
{
	CLIENT_FUNCTION(GetNumber, 0x84E030, __cdecl, double, (lua_State*, int32_t))
	CLIENT_FUNCTION(IsNumber, 0x84DF20, __cdecl, int32_t, (lua_State*, int32_t))
	CLIENT_FUNCTION(LoadFunctions, 0x5120E0, __cdecl, int, ())
	CLIENT_FUNCTION(PushNil, 0x84E280, __cdecl, int, (lua_State*))
	CLIENT_FUNCTION(PushNumber, 0x84E2A0, __cdecl, int, (lua_State* L, double value))
	CLIENT_FUNCTION(PushString, 0x84E350, __cdecl, int, (lua_State*, char const*))
	CLIENT_FUNCTION(RegisterFunction, 0x817F90, __cdecl, int, (char*, void*))
}

namespace Spell_C
{
	CLIENT_FUNCTION(IsSpellKnown, 0x5D3560, __cdecl, int, (uint32_t))
}

namespace SpellParser
{
	CLIENT_FUNCTION(ParseText, 0x57ABC0, __cdecl, void, (void*, void*, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t))
}

namespace SStr
{
	CLIENT_FUNCTION(Printf, 0x76F070, __cdecl, int, (char*, uint32_t, char*, ...))
}

namespace World
{
	CLIENT_FUNCTION(LoadMap, 0x781430, __cdecl, void, (char*, C3Vector*, uint32_t))
	CLIENT_FUNCTION(UnloadMap, 0x783180, __cdecl, void, ())
}
