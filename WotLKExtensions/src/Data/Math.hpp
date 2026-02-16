#pragma once

#include <cstdint>

struct C2Vector
{
    float x = 0.f;
    float y = 0.f;
};

struct C3Vector
{
    float x;
    float y;
    float z;
};

class NTempest
{
public:
    static bool DistanceSquaredFromEdge(int32_t index, void* data, C2Vector* vec, float* f);

private:
    NTempest() = delete;
    ~NTempest() = delete;
};
