#pragma once

#include <SharedDefines.hpp>

#include <cstdint>

class CGPetInfo
{
public:
    static WoWGUID GetPet(int32_t index);

private:
    CGPetInfo() = delete;
    ~CGPetInfo() = delete;
};
