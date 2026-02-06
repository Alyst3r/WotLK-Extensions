#include <Client/Misc.hpp>
#include <Client/SStr.hpp>

#include <ctime>

void Misc::ApplyPatches()
{
#if NOAMMO_PATCH
    uint8_t byteArray[] = { 0xE9, 0xBA, 0x00, 0x00, 0x00 };
    Util::OverwriteBytesAtAddress(0x809540, byteArray, sizeof(byteArray));
#endif

#if ITEMMODEXT_PATCH
    // Code needs to be un-commented when you decide to add some custom mods
    // ofc can replace "ITEM_MOD_TEST" with your own
    //const char* customItemModStrings[1] =
    //{
    //    "ITEM_MOD_TEST"
    //};

    memcpy(&itemModTable, (const void*)0xAD6640, 0xC4);
    Util::OverwriteUInt32AtAddress(0x5DC1EB, (uint32_t)&itemModTable);
    Util::OverwriteUInt32AtAddress(0x629211, (uint32_t)&itemModTable);
    Util::OverwriteUInt32AtAddress(0x6292E6, (uint32_t)&itemModTable);
    Util::OverwriteUInt32AtAddress(0x62BC60, (uint32_t)&itemModTable);
    Util::OverwriteUInt32AtAddress(0x62BE67, (uint32_t)&itemModTable);
    //
    Util::OverwriteUInt32AtAddress(0x62BD82, (uint32_t)&itemModTable[45]);
    // when you read code in ida, this table is kinda dumb but what can you do about it
    memcpy(&itemModTableVal, (const void*)0xA25F78, 0x94);
    Util::OverwriteUInt32AtAddress(0x62BC43, (uint32_t)&itemModTableVal);
    Util::SetByteAtAddress((void*)0x62BC4E, (uint8_t)(sizeof(itemModTableVal)/4));
    Util::OverwriteUInt32AtAddress(0x62BC59, (uint32_t)&itemModTableVal);
    Util::OverwriteUInt32AtAddress(0x62BE4A, (uint32_t)&itemModTableVal);
    Util::SetByteAtAddress((void*)0x62BE55, (uint8_t)(sizeof(itemModTableVal) / 4));
    Util::OverwriteUInt32AtAddress(0x62BE60, (uint32_t)&itemModTableVal);

    //for (uint32_t i = 0; i < sizeof(customItemModStrings) / 4; i++)
    //    itemModTable[i + 49] = (uint32_t)customItemModStrings[i];

    //for (uint32_t j = 37; j < sizeof(itemModTableVal) / 4; j++)
    //    itemModTableVal[j] = j + 12;
#endif

    // this one is non-optional, it's WoWTime fix I guess
    // and don't let me get started how retarded original idea behind packing like this is
    ApplyWoWTimePatches();
}

void Misc::ApplyWoWTimePatches()
{
    // This patches original function to call custom function from dll, otherwise I would need to patch a lot of pointers
    uint8_t byteArray[] = { 0x8B, 0x55, 0x08, 0x50, 0x52, 0xE8, 0x00, 0x00, 0x00, 0x00, 0x83, 0xC4, 0x08, 0x5D, 0xC3 };
    Util::OverwriteBytesAtAddress(0x76CA56, byteArray, sizeof(byteArray));
    Util::OverwriteUInt32AtAddress(0x76CA5C, (uint32_t)&PackWoWTimeToDword - 0x76CA60);
    //
    Util::OverwriteUInt32AtAddress(0x4C989C, (uint32_t)&PackTimeDataToDword - 0x4C98A0);
    Util::OverwriteUInt32AtAddress(0x4C98C2, (uint32_t)&PackTimeDataToDword - 0x4C98C6);
    //
    Util::OverwriteUInt32AtAddress(0x76CAD4, (uint32_t)&UnpackWoWTime - 0x76CAD8);
    Util::OverwriteUInt32AtAddress(0x76CB19, (uint32_t)&UnpackWoWTime - 0x76CB1D);
    Util::OverwriteUInt32AtAddress(0x76CB93, (uint32_t)&UnpackWoWTime - 0x76CB97);
    //
    Util::OverwriteUInt32AtAddress(0x76DA89, (uint32_t)&GetTimeString - 0x76DA8D);
    Util::OverwriteUInt32AtAddress(0x76DA9F, (uint32_t)&GetTimeString - 0x76DAA3);
    Util::OverwriteUInt32AtAddress(0x7E27B7, (uint32_t)&GetTimeString - 0x7E27BB);
    Util::OverwriteUInt32AtAddress(0x7E2AC7, (uint32_t)&GetTimeString - 0x7E2ACB);
    // Patching a bunch of year >= 31 checks
    Util::SetByteAtAddress((void*)0x5B7ACC, 0xEB);
    Util::SetByteAtAddress((void*)0x5B7ACD, 0x08);
    Util::OverwriteBytesAtAddress((void*)0x5B82C0, 0xFF, 0x03);
    Util::SetByteAtAddress((void*)0x5B82C3, 0x7F);
    Util::SetByteAtAddress((void*)0x5B8F35, 0xEB);
    Util::SetByteAtAddress((void*)0x5B8F99, 0xEB);
    Util::SetByteAtAddress((void*)0x5B8F9A, 0x08);
    Util::OverwriteBytesAtAddress((void*)0x5BFF44, 0x90, 0x03);
    Util::SetByteAtAddress((void*)0x5BFF58, 0xEB);
    Util::OverwriteBytesAtAddress((void*)0x5C01F9, 0x90, 0x03);
    Util::OverwriteBytesAtAddress((void*)0x5C01FF, 0x90, 0x02);
    Util::OverwriteBytesAtAddress((void*)0x5C04BF, 0x90, 0x03);
    Util::OverwriteBytesAtAddress((void*)0x5C04C5, 0x90, 0x02);
    Util::SetByteAtAddress((void*)0x5C2890, 0xEB);
    Util::SetByteAtAddress((void*)0x5C2891, 0x08);
    Util::OverwriteBytesAtAddress((void*)0x76C4A8, 0x90, 0x05);
}

void Misc::PackTimeDataToDword(uint32_t* packedTime, int32_t minute, int32_t hour, int32_t weekDay, int32_t monthDay, int32_t month, int32_t year, int32_t flags)
{
    uint32_t temp = 0;
    temp += minute & 63;
    temp += (hour & 31) << 6;
    temp += (weekDay & 7) << 11;
    temp += (monthDay & 63) << 14;
    temp += (month & 15) << 20;
    temp += year >= 31 ? 31 << 24 : (year & 31) << 24;
    temp += (flags & 3) << 29;

    *packedTime = temp;
}

void Misc::PackWoWTimeToDword(uint32_t* dword, WoWTime* time)
{
    uint32_t temp = 0;
    temp += time->minute & 63;
    temp += (time->hour & 31) << 6;
    temp += (time->weekDay & 7) << 11;
    temp += (time->monthDay & 63) << 14;
    temp += (time->month & 15) << 20;
    temp += time->year >= 31 ? 31 << 24 : (time->year & 31) << 24;
    temp += (time->flags & 3) << 29;

    *dword = temp;
}

void Misc::UnpackWoWTime(uint32_t packedTime, int32_t* minute, int32_t* hour, int32_t* weekDay, int32_t* monthDay, int32_t* month, int32_t* year, int32_t* flags)
{
    if (minute)
    {
        if ((packedTime & 63) == 63)
            *minute = -1;
        else
            *minute = packedTime & 63;
    }

    if (hour)
    {
        if (((packedTime >> 6) & 31) == 31)
            *hour = -1;
        else
            *hour = (packedTime >> 6) & 31;
    }

    if (weekDay)
    {
        if (((packedTime >> 11) & 7) == 7)
            *weekDay = -1;
        else
            *weekDay = (packedTime >> 11) & 7;
    }

    if (monthDay)
    {
        if (((packedTime >> 14) & 63) == 63)
            *monthDay = -1;
        else
            *monthDay = (packedTime >> 14) & 63;
    }

    if (month)
    {
        if (((packedTime >> 20) & 15) == 15)
            *month = -1;
        else
            *month = (packedTime >> 20) & 15;
    }

    if (year)
            *year = (packedTime >> 24) & 31 + yearOffsetMult * 32;

    if (flags)
    {
        if (((packedTime >> 29) & 3) == 3)
            *flags = -1;
        else
            *flags = (packedTime >> 29) & 3;
    }
}

char* Misc::GetTimeString(WoWTime* a1, char* a2, uint32_t a3)
{
    // Aleist3r: giving up a couple things from original function, originally it was doing a bunch of data & num operations in the first if
    // after that it's checking if values are >= 0...
    if (a1->minute > -1 && a1->hour > -1 && a1->weekDay > -1 && a1->monthDay > -1 && a1->month > -1 && a1->year > -1)
    {
        const char* weekDays[7] = {
            "Sun", "Mon", "Tue", "Wed", "Thu", "Fri", "Sat"
        };

        char month[8];
        char monthDay[8];
        char year[8];
        char weekDay[8];
        char hour[8];
        char minute[8];

        SStr::Printf(month, 8, "%i", a1->month + 1);
        SStr::Printf(monthDay, 8, "%i", a1->monthDay + 1);
        SStr::Printf(year, 8, "%i", a1->year + 2000);
        SStr::Printf(weekDay, 8, "%s", weekDays[a1->weekDay]);
        SStr::Printf(hour, 8, "%i", a1->hour);
        SStr::Printf(minute, 8, "%i", a1->minute);

        SStr::Printf(a2, a3, "%s/%s/%s (%s) %s:%s", month, monthDay, year, weekDay, hour, minute);
    }
    else
        SStr::Printf(a2, a3, "Not Set");

    return a2;
}

void Misc::SetYearOffsetMultiplier()
{
    time_t now = time(0);
    tm* ltm = localtime(&now);

    yearOffsetMult = (ltm->tm_year - 100) / 32;
}
