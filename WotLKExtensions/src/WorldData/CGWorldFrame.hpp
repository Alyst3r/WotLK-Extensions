#pragma once

#include <Data/Structs.hpp>

class CGWorldFrame
{
public:
    static void ApplyPatches();

    static CGWorldFrame* GetInstance();

    static int32_t HitTestPointEx(CGWorldFrame* thisFrame, int32_t a2, int32_t a3, int32_t a4, HitTestResult* a5);
    static void OnWorldRender(CGWorldFrame* thisFrame);
    static void __fastcall OnWorldRenderEx(CGWorldFrame* thisFrame, uint32_t unused);
    static int32_t Pos3Dto2D(CGWorldFrame* thisFrame, C3Vector* pos3d, C3Vector* pos2d, uint32_t* flags);

private:
    CGWorldFrame() = delete;
    ~CGWorldFrame() = delete;

    static int32_t HitTestPoint(CGWorldFrame* thisFrame, int32_t a2, int32_t a3, int32_t a4, HitTestResult* a5);
};
