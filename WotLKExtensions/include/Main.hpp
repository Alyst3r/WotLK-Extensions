#pragma once

#include <CDBCMgr/CDBCMgr.hpp>
#include <GameObjects/Player.hpp>
#include <System/CustomLua.hpp>
#include <System/CustomPacket.hpp>
#include <System/Misc.hpp>
#include <WorldData/World.hpp>

class Main
{
public:
    static void OnAttach();
    static void Init();
};
