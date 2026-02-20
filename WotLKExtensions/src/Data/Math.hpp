#pragma once

#include <cstdint>

struct C2Vector
{
    float m_x = 0.f;
    float m_y = 0.f;
};

struct C3Vector
{
    float m_x = 0.f;
    float m_y = 0.f;
    float m_z = 0.f;
};

class NTempest
{
public:
    static bool DistanceSquaredFromEdge(int32_t index, void* data, C2Vector* vec, float* f);

private:
    NTempest() = delete;
    ~NTempest() = delete;
};
