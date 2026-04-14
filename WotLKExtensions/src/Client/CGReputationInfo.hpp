#pragma once

#include <cstdint>

class CGReputationInfo
{
public:
    static int32_t GetFactionStanding(int32_t faction);

private:
    CGReputationInfo() = delete;
    ~CGReputationInfo() = delete;
};
