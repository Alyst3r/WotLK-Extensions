#pragma once

#include <Windows.h>
#include <cstdint>

struct DBItemCache;
struct DBNameCache;
struct DBPetitionCache;

static volatile uint8_t& renderFlags1 = *reinterpret_cast<volatile uint8_t*>(0xCD774C);
static volatile uint8_t& renderFlags2 = *reinterpret_cast<volatile uint8_t*>(0xCD774D);
static volatile uint8_t& renderFlags3 = *reinterpret_cast<volatile uint8_t*>(0xCD774E);
static volatile uint8_t& renderFlags4 = *reinterpret_cast<volatile uint8_t*>(0xCD774F);

static int32_t* const g_currentMapID = reinterpret_cast<int32_t*>(0xBD088C);
static HWND* const g_window = reinterpret_cast<HWND*>(0xD41620);

static uint32_t* g_actionButtonsArray = reinterpret_cast<uint32_t*>(0xC1DED8);
static uint32_t* g_actionBarSpellIDArray = reinterpret_cast<uint32_t*>(0xC1E358);

static DBItemCache* g_itemDBCache = reinterpret_cast<DBItemCache*>(0xC5D828);
static DBNameCache* g_nameDBCache = reinterpret_cast<DBNameCache*>(0xC5D938);
static DBPetitionCache* g_petitionDBCache = reinterpret_cast<DBPetitionCache*>(0xC5DBE0);
