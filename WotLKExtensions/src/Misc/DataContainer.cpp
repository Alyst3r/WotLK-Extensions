#include <Misc/DataContainer.hpp>

#include <ctime>

DataContainer::DataContainer() : m_lfgRolesCDBC(LFGRoles::GetInstance()), m_zoneLightCDBC(ZoneLight::GetInstance()),
    m_zoneLightPointCDBC(ZoneLightPoint::GetInstance())
{
}

DataContainer::~DataContainer()
{
}

DataContainer& DataContainer::GetInstance()
{
    static DataContainer instance;

    return instance;
}

void DataContainer::AddLuaFunction(const char* name, void* ptr)
{
    m_luaFunctions.insert(std::make_pair(name, ptr));
}

std::unordered_map<const char*, void*>& DataContainer::GetLuaFunctionMap()
{
    return m_luaFunctions;
}

void DataContainer::AddPacketHandler(uint32_t opcode, CNetClientCustomPacket packetData)
{
    m_packetData.insert(std::make_pair(opcode, packetData));
}

std::unordered_map <uint32_t, CNetClientCustomPacket>& DataContainer::GetPacketHandlerMap()
{
    return m_packetData;
}

void DataContainer::LoadLFGRolesDB()
{
    m_lfgRolesCDBC.LoadDB();
}

void DataContainer::GetLFGRolesRow(LFGRolesRow& row, int32_t index)
{
    m_lfgRolesCDBC.GetRow(row, index);
}

void DataContainer::LoadZoneLightDB()
{
    m_zoneLightCDBC.LoadDB();
}

void DataContainer::GetZoneLightRow(ZoneLightRow& row, int32_t index)
{
    m_zoneLightCDBC.GetRow(row, index);
}

int32_t DataContainer::GetZoneLightRowMinIndex() const
{
    return m_zoneLightCDBC.GetMinIndex();
}
int32_t DataContainer::GetZoneLightRowMaxIndex() const
{
    return m_zoneLightCDBC.GetMaxIndex();
}

void DataContainer::LoadZoneLightPointDB()
{
    m_zoneLightPointCDBC.LoadDB();
}

void DataContainer::GetZoneLightPointRow(ZoneLightPointRow& row, int32_t index)
{
    m_zoneLightPointCDBC.GetRow(row, index);
}

int32_t DataContainer::GetZoneLightPointRowMinIndex() const
{
    return m_zoneLightPointCDBC.GetMinIndex();
}

int32_t DataContainer::GetZoneLightPointRowMaxIndex() const
{
    return m_zoneLightPointCDBC.GetMaxIndex();
}

uint32_t* DataContainer::GetRaceTablePtr()
{
    return m_raceNameTable;
}

uint32_t* DataContainer::GetMemoryTablePtr()
{
    return m_memoryTable;
}

uint8_t* DataContainer::GetClassRoleMaskTablePtr()
{
    return m_classRoleMask;
}

uint32_t DataContainer::GetYearOffsetMultiplier() const
{
    return m_yearOffsetMult;
}

void DataContainer::SetYearOffsetMultiplier()
{
    time_t now = time(0);
    tm* ltm = localtime(&now);

    m_yearOffsetMult = (ltm->tm_year - 100) / 32;
}

void DataContainer::AddZoneLight(ZoneLightData& lightData)
{
    m_zoneLightData.push_back(lightData);
}

std::vector<ZoneLightData>& DataContainer::GetZoneLightData()
{
    return m_zoneLightData;
}

int32_t DataContainer::GetCustomCombatRating(int8_t index) const
{
    return m_playerFields.m_combatRating[index];
}

void DataContainer::SetCustomCombatRating(int8_t index, int32_t value)
{
    m_playerFields.m_combatRating[index] = value;
}
