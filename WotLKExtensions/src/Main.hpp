#pragma once

#include <CDBCMgr/CDBCMgr.hpp>
#include <Client/CustomLua.hpp>
#include <Client/CustomPacket.hpp>
#include <Client/Misc.hpp>
#include <GameObjects/Player.hpp>
#include <WorldData/World.hpp>

class Main
{
public:
    static void OnAttach();
    static void Init();

private:
    Main() = delete;
    ~Main() = delete;
};
