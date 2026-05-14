#pragma once

#include <cstdint>

struct lua_State;

typedef int64_t WoWGUID;

static uint32_t dummy = 0;

static uint32_t sTextGreen = 0xFF00FF00;
static uint32_t sTextGreen2 = 0xFF40C040;
static uint32_t sTextGrey = 0xFF808080;
static uint32_t sTextLightBlue = 0xFF88AAFF;
static uint32_t sTextLightBlue2 = 0xFF66BBFF;
static uint32_t sTextOrange = 0xFFFF8040;
static uint32_t sTextPink = 0xFFFF80FF;
static uint32_t sTextRed = 0xFFFF2020;
static uint32_t sTextWhite = 0xFFFFFFFF;
static uint32_t sTextYellow = 0xFFFFD200;
static uint32_t sTextYellow2 = 0xFFFFFF00;

static uint32_t sItemQualityPoor = 0xFF9D9D9D;
static uint32_t sItemQualityCommon = 0xFFFFFFFF;
static uint32_t sItemQualityUncommon = 0xFF1EFF00;
static uint32_t sItemQualityRare = 0xFF0070DD;
static uint32_t sItemQualityEpic = 0xFFA335EE;
static uint32_t sItemQualityLegendary = 0xFFFF8000;
static uint32_t sItemQualityArtifact = 0xFFE6CC80;
static uint32_t sItemQualityHeirloom = 0xFFE6CC80;

static char* sStringRed = "|cffff2020";

static uint32_t* sDifficultyColors[] =
{
    &sTextGrey, &sTextGreen2, &sTextYellow2, &sTextOrange, &sTextRed
};

static char* sDifficultyIndicators[]
{
    "", "[+] ", "[++] ", "[+++] ", "[-] "
};

static uint32_t* sItemQualityColors[] =
{
    &sItemQualityPoor, &sItemQualityCommon, &sItemQualityUncommon, &sItemQualityRare,
    &sItemQualityEpic, &sItemQualityLegendary, &sItemQualityArtifact, &sItemQualityHeirloom
};
