#pragma once

#include <CDBCMgr/CDBCDefs/LFGRoles.hpp>
#include <CDBCMgr/CDBCDefs/ZoneLight.hpp>
#include <CDBCMgr/CDBCDefs/ZoneLightPoint.hpp>
#include <Client/CNetClient.hpp>
#include <GameObjects/CGPlayer.hpp>
#include <WorldData/ZoneLightData.hpp>

#include <cstdint>
#include <unordered_map>
#include <vector>

struct CDataStore;

class DataContainer
{
public:
    static DataContainer& GetInstance();

    void AddLuaFunction(const char* name, void* ptr);
    std::unordered_map<const char*, void*>& GetLuaFunctionMap();

    void AddPacketHandler(uint32_t opcode, CNetClientCustomPacket packetData);
    std::unordered_map <uint32_t, CNetClientCustomPacket>& GetPacketHandlerMap();

    void LoadLFGRolesDB();
    void GetLFGRolesRow(LFGRolesRow& row, int32_t index);

    void LoadZoneLightDB();
    void GetZoneLightRow(ZoneLightRow& row, int32_t index);
    int32_t GetZoneLightRowMinIndex() const;
    int32_t GetZoneLightRowMaxIndex() const;

    void LoadZoneLightPointDB();
    void GetZoneLightPointRow(ZoneLightPointRow& row, int32_t index);
    int32_t GetZoneLightPointRowMinIndex() const;
    int32_t GetZoneLightPointRowMaxIndex() const;

    std::vector<const char*>& GetSpellVariableData();

    uint32_t* GetRaceTablePtr();
    uint32_t* GetMemoryTablePtr();
    uint8_t* GetClassRoleMaskTablePtr();

    uint32_t GetYearOffsetMultiplier() const;
    void SetYearOffsetMultiplier();

    void AddZoneLight(ZoneLightData& lightData);
    std::vector<ZoneLightData>& GetZoneLightData();

    int32_t GetCustomCombatRating(int8_t index) const;
    void SetCustomCombatRating(int8_t index, int32_t value);

private:
    std::unordered_map<const char*, void*> m_luaFunctions;
    std::unordered_map <uint32_t, CNetClientCustomPacket> m_packetData;

    LFGRoles& m_lfgRolesCDBC;
    ZoneLight& m_zoneLightCDBC;
    ZoneLightPoint& m_zoneLightPointCDBC;

    std::vector<const char*> m_spellVariables;

    std::vector<uint32_t> m_raceNameTable;
    std::vector<uint32_t> m_memoryTable;

    // Just for clarity's sake, class role masks go as followed
    // ID0, War, Pal, Hun, Rog, Pri, DK, Sha, Mag, Warl, ID10, Dru
    // bitmasks: 1 - leader, 2 - tank, 4 - healer, 8 - dps
    // so for example warrior is: leader + tank + dps -> 0x01 + 0x02 + 0x08 = 0x0B
    // this table is only ever used if you don't use custom dbc
    std::vector<uint8_t> m_classRoleMask =
    {
        0x00, 0x0B, 0x0F, 0x09, 0x09, 0x0D, 0x0B, 0x0D,	0x09, 0x09, 0x00, 0x0F, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
    };

    uint32_t m_yearOffsetMult = 0;

    std::vector<ZoneLightData> m_zoneLightData;

    CGPlayerCustomFields m_playerFields;

    DataContainer();
    DataContainer(const DataContainer&) = delete;
    ~DataContainer();

    DataContainer& operator=(const DataContainer&) = delete;
};
