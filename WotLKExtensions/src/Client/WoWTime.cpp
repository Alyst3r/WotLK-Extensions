#include <Client/SStr.hpp>
#include <Client/WoWTime.hpp>
#include <Misc/DataContainer.hpp>
#include <Misc/Util.hpp>

void WoWTime::ApplyWoWTimePatches()
{
    // This patches original function to call custom function from dll, otherwise I would need to patch a lot of pointers
    uint8_t byteArray[] = { 0x8B, 0x55, 0x08, 0x50, 0x52, 0xE8, 0x00, 0x00, 0x00, 0x00, 0x83, 0xC4, 0x08, 0x5D, 0xC3 };
    Util::OverwriteBytesAtAddress(0x76CA56, byteArray, sizeof(byteArray));
    Util::OverwriteUInt32AtAddress(0x76CA5C, reinterpret_cast<uint32_t>(&PackWoWTimeToDword) - 0x76CA60);
    //
    Util::OverwriteUInt32AtAddress(0x4C989C, reinterpret_cast<uint32_t>(&PackTimeDataToDword) - 0x4C98A0);
    Util::OverwriteUInt32AtAddress(0x4C98C2, reinterpret_cast<uint32_t>(&PackTimeDataToDword) - 0x4C98C6);
    //
    Util::OverwriteUInt32AtAddress(0x76CAD4, reinterpret_cast<uint32_t>(&UnpackWoWTime) - 0x76CAD8);
    Util::OverwriteUInt32AtAddress(0x76CB19, reinterpret_cast<uint32_t>(&UnpackWoWTime) - 0x76CB1D);
    Util::OverwriteUInt32AtAddress(0x76CB93, reinterpret_cast<uint32_t>(&UnpackWoWTime) - 0x76CB97);
    //
    Util::OverwriteUInt32AtAddress(0x76DA89, reinterpret_cast<uint32_t>(&GetTimeString) - 0x76DA8D);
    Util::OverwriteUInt32AtAddress(0x76DA9F, reinterpret_cast<uint32_t>(&GetTimeString) - 0x76DAA3);
    Util::OverwriteUInt32AtAddress(0x7E27B7, reinterpret_cast<uint32_t>(&GetTimeString) - 0x7E27BB);
    Util::OverwriteUInt32AtAddress(0x7E2AC7, reinterpret_cast<uint32_t>(&GetTimeString) - 0x7E2ACB);
    // Patching a bunch of year >= 31 checks
    Util::SetByteAtAddress(reinterpret_cast<void*>(0x5B7ACC), 0xEB);
    Util::SetByteAtAddress(reinterpret_cast<void*>(0x5B7ACD), 0x08);
    Util::OverwriteBytesAtAddress(reinterpret_cast<void*>(0x5B82C0), 0xFF, 0x03);
    Util::SetByteAtAddress(reinterpret_cast<void*>(0x5B82C3), 0x7F);
    Util::SetByteAtAddress(reinterpret_cast<void*>(0x5B8F35), 0xEB);
    Util::SetByteAtAddress(reinterpret_cast<void*>(0x5B8F99), 0xEB);
    Util::SetByteAtAddress(reinterpret_cast<void*>(0x5B8F9A), 0x08);
    Util::OverwriteBytesAtAddress(reinterpret_cast<void*>(0x5BFF44), 0x90, 0x03);
    Util::SetByteAtAddress(reinterpret_cast<void*>(0x5BFF58), 0xEB);
    Util::OverwriteBytesAtAddress(reinterpret_cast<void*>(0x5C01F9), 0x90, 0x03);
    Util::OverwriteBytesAtAddress(reinterpret_cast<void*>(0x5C01FF), 0x90, 0x02);
    Util::OverwriteBytesAtAddress(reinterpret_cast<void*>(0x5C04BF), 0x90, 0x03);
    Util::OverwriteBytesAtAddress(reinterpret_cast<void*>(0x5C04C5), 0x90, 0x02);
    Util::SetByteAtAddress(reinterpret_cast<void*>(0x5C2890), 0xEB);
    Util::SetByteAtAddress(reinterpret_cast<void*>(0x5C2891), 0x08);
    Util::OverwriteBytesAtAddress(reinterpret_cast<void*>(0x76C4A8), 0x90, 0x05);
}

void WoWTime::PackTimeDataToDword(uint32_t* packedTime, int32_t minute, int32_t hour, int32_t weekDay, int32_t monthDay, int32_t month, int32_t year, int32_t flags)
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

void WoWTime::PackWoWTimeToDword(uint32_t* dword, WoWTime* time)
{
    uint32_t temp = 0;
    temp += time->m_minute & 63;
    temp += (time->m_hour & 31) << 6;
    temp += (time->m_weekDay & 7) << 11;
    temp += (time->m_monthDay & 63) << 14;
    temp += (time->m_month & 15) << 20;
    temp += time->m_year >= 31 ? 31 << 24 : (time->m_year & 31) << 24;
    temp += (time->m_flags & 3) << 29;

    *dword = temp;
}

void WoWTime::UnpackWoWTime(uint32_t packedTime, int32_t* minute, int32_t* hour, int32_t* weekDay, int32_t* monthDay, int32_t* month, int32_t* year, int32_t* flags)
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
        *year = (packedTime >> 24) & 31 + DataContainer::GetInstance().GetYearOffsetMultiplier() * 32;

    if (flags)
    {
        if (((packedTime >> 29) & 3) == 3)
            *flags = -1;
        else
            *flags = (packedTime >> 29) & 3;
    }
}

char* WoWTime::GetTimeString(WoWTime* a1, char* a2, uint32_t a3)
{
    // Aleist3r: giving up a couple things from original function, originally it was doing a bunch of data & num operations in the first if
    // after that it's checking if values are >= 0...
    if (a1->m_minute > -1 && a1->m_hour > -1 && a1->m_weekDay > -1 && a1->m_monthDay > -1 && a1->m_month > -1 && a1->m_year > -1)
    {
        const char* weekDays[7] =
        {
            "Sun", "Mon", "Tue", "Wed", "Thu", "Fri", "Sat"
        };

        char month[8] = { 0 };
        char monthDay[8] = { 0 };
        char year[8] = { 0 };
        char weekDay[8] = { 0 };
        char hour[8] = { 0 };
        char minute[8] = { 0 };

        SStr::Printf(month, 8, "%i", a1->m_month + 1);
        SStr::Printf(monthDay, 8, "%i", a1->m_monthDay + 1);
        SStr::Printf(year, 8, "%i", a1->m_year + 2000);
        SStr::Printf(weekDay, 8, "%s", weekDays[a1->m_weekDay]);
        SStr::Printf(hour, 8, "%i", a1->m_hour);
        SStr::Printf(minute, 8, "%i", a1->m_minute);

        SStr::Printf(a2, a3, "%s/%s/%s (%s) %s:%s", month, monthDay, year, weekDay, hour, minute);
    }
    else
        SStr::Printf(a2, a3, "Not Set");

    return a2;
}
