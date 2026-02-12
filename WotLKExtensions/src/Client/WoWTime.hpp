#pragma once

#include <cstdint>

// Aleist3r: afaik it's not a full structure but I don't need the rest defined
struct WoWTime
{
    int32_t m_minute;
    int32_t m_hour;
    int32_t m_weekDay;
    int32_t m_monthDay;
    int32_t m_month;
    int32_t m_year;
    int32_t m_flags;

    static void ApplyWoWTimePatches();
    static char* GetTimeString(WoWTime* thisTime, char* a2, uint32_t a3);
    static void PackTimeDataToDword(uint32_t* packedTime, int32_t minute, int32_t hour, int32_t weekDay, int32_t monthDay, int32_t month, int32_t year, int32_t flags);
    static void PackWoWTimeToDword(uint32_t* dword, WoWTime* time);
    static void UnpackWoWTime(uint32_t packedTime, int32_t* minute, int32_t* hour, int32_t* weekDay, int32_t* monthDay, int32_t* month, int32_t* year, int32_t* flags);
};
