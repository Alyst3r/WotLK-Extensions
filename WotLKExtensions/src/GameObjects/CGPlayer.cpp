#include <GameObjects/CGPlayer.hpp>

bool CGPlayer::IsDeadOrGhost(CGPlayer* thisPlayer)
{
    return reinterpret_cast<bool (__thiscall*)(CGPlayer*)>(0x6DAC10)(thisPlayer);
}
