#pragma once

#include <Windows.h>

#include <CDBCMgr/CDBCMgr.hpp>
#include <Client/CustomLua.hpp>
#include <Client/CNetClient.hpp>
#include <Client/Misc.hpp>
#include <Client/WoWTime.hpp>
#include <GameObjects/CGPlayer.hpp>
#include <Misc/DataContainer.hpp>
#include <WorldData/ZoneLightData.hpp>

#include <PatchConfig.hpp>

class Main
{
public:
    static void OnAttach();
    static void Init();

private:
    Main() = delete;
    ~Main() = delete;
};
