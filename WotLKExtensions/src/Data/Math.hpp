#pragma once

#include <Data/Structs.hpp>

class NTempest
{
public:
    static bool DistanceSquaredFromEdge(int32_t index, void* data, C2Vector* vec, float* f);

private:
    NTempest() = delete;
    ~NTempest() = delete;
};
