#pragma once

#include <Data/Structs.hpp>

class CGWorldFrame
{
public:
    static void ApplyPatches();

    static CGWorldFrame* GetInstance();

    static int32_t HitTestPointEx(CGWorldFrame* thisFrame, int32_t a2, int32_t a3, int32_t a4, HitTestResult* a5);

private:
    CGWorldFrame() = delete;
    ~CGWorldFrame() = delete;

    static int32_t HitTestPoint(CGWorldFrame* thisFrame, int32_t a2, int32_t a3, int32_t a4, HitTestResult* a5);
};
