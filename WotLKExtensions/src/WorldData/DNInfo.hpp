#pragma once

#include <cstdint>

class DNInfo
{
public:
    static void AddZoneLight(void* thisDNInfo, int32_t lightId, float f);
    static void* GetDNInfoPtr();

private:
    DNInfo() = delete;
    ~DNInfo() = delete;
};
