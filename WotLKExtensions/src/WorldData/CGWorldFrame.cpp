#include <Client/Editor/EditorObject.hpp>
#include <Misc/Util.hpp>
#include <WorldData/CGWorldFrame.hpp>

void CGWorldFrame::ApplyPatches()
{
    Util::OverwriteUInt32AtAddress(0x4FA13B, reinterpret_cast<uint32_t>(&HitTestPointEx) - 0x4FA13F);
    Util::OverwriteUInt32AtAddress(0x4FA5C1, reinterpret_cast<uint32_t>(&HitTestPointEx) - 0x4FA5C5);
}

CGWorldFrame* CGWorldFrame::GetInstance()
{
    return *reinterpret_cast<CGWorldFrame**>(0xB7436C);
}

int32_t CGWorldFrame::HitTestPoint(CGWorldFrame* thisFrame, int32_t a2, int32_t a3, int32_t a4, HitTestResult* a5)
{
    return reinterpret_cast<int32_t (__thiscall*)(CGWorldFrame*, int32_t, int32_t, int32_t, HitTestResult*)>(0x4F9DA0)(thisFrame, a2, a3, a4, a5);
}

int32_t CGWorldFrame::HitTestPointEx(CGWorldFrame* thisFrame, int32_t a2, int32_t a3, int32_t a4, HitTestResult* a5)
{
    int32_t result = HitTestPoint(thisFrame, a2, a3, a4, a5);

    return result;
}
