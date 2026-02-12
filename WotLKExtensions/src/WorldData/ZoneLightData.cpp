#include <CDBCMgr/CDBCDefs/ZoneLight.hpp>
#include <CDBCMgr/CDBCDefs/ZoneLightPoint.hpp>
#include <Data/Structs.hpp>
#include <Misc/DataContainer.hpp>
#include <Misc/Util.hpp>
#include <WorldData/DNInfo.hpp>
#include <WorldData/ZoneLightData.hpp>

void ZoneLightData::ApplyZoneLightsExtensions()
{
    Util::OverwriteUInt32AtAddress(0x781426, (uint32_t)&FillZoneLightData - 0x78142A);
    // sets the check for map id to > -1 so it's always true unless no map is loaded
    Util::OverwriteUInt32AtAddress(0x781730, 0xFFFFFFFF);
    Util::OverwriteUInt32AtAddress(0x781751, (uint32_t)&FindAndAddZoneLightEx - 0x781755);
    // calls nullsub_3 instead of original function
    Util::OverwriteUInt32AtAddress(0x9E0360, 0x5EEB70);
}

void ZoneLightData::FillZoneLightData()
{
    int32_t zoneLightMin = GlobalCDBCMap.getIndexRange("ZoneLight").first;
    int32_t zoneLightMax = GlobalCDBCMap.getIndexRange("ZoneLight").second;
    int32_t zoneLightPointMin = GlobalCDBCMap.getIndexRange("ZoneLightPoint").first;
    int32_t zoneLightPointMax = GlobalCDBCMap.getIndexRange("ZoneLightPoint").second;
    uint32_t counter = 1;

    for (uint32_t i = zoneLightMin; i <= zoneLightMax; i++)
    {
        ZoneLightData data;
        ZoneLightRow* row = GlobalCDBCMap.getRow<ZoneLightRow>("ZoneLight", i);
        std::vector<C2Vector> points{};

        if (!row)
            continue;

        data.m_mapID = row->m_mapID;
        data.m_lightID = row->m_lightID;

        for (uint32_t j = counter; j <= zoneLightPointMax; j++)
        {
            ZoneLightPointRow* tempRow = GlobalCDBCMap.getRow<ZoneLightPointRow>("ZoneLightPoint", j);
            C2Vector tempVec = { 0 };

            counter++;

            if (!tempRow || tempRow->m_zoneLightID < row->m_ID)
                continue;

            if (tempRow->m_zoneLightID > row->m_ID)
                break;

            tempVec.x = tempRow->m_positionX;
            tempVec.y = tempRow->m_positionY;

            points.push_back(tempVec);

            if (j == zoneLightPointMin)
            {
                data.m_minX, data.m_maxX = tempVec.x;
                data.m_maxY, data.m_maxY = tempVec.y;
            }

            if (data.m_minX > tempVec.x)
                data.m_minX = tempVec.x;

            if (data.m_minY > tempVec.y)
                data.m_minY = tempVec.y;

            if (data.m_maxX < tempVec.x)
                data.m_maxX = tempVec.x;

            if (data.m_maxY < tempVec.y)
                data.m_maxY = tempVec.y;

            if (points.size())
                data.m_pointData = points;
        }

        data.m_minX -= 50.f;
        data.m_minY -= 50.f;
        data.m_maxX += 50.f;
        data.m_maxY += 50.f;

        DataContainer::GetInstance().AddZoneLight(data);
    }
}

void ZoneLightData::FindAndAddZoneLightEx(C3Vector* vec)
{
    auto& zoneLightData = DataContainer::GetInstance().GetZoneLightData();
    void* g_dnInfo = DNInfo::GetDNInfoPtr();
    int32_t currentMap = *reinterpret_cast<int32_t*>(0xADFBC4);
    C2Vector vec2d{ -(vec->y - 17066.666f), -(vec->x - 17066.666f) };

    if (!zoneLightData.size())
        return;

    for (auto& it : zoneLightData)
    {
        if (it.m_mapID == currentMap && it.m_minX <= vec2d.x && it.m_minY <= vec2d.y && it.m_maxX >= vec2d.x && it.m_maxY >= vec2d.y)
        {
            float temp = 0.f;
            bool isWithin = NTempest::DistanceSquaredFromEdge(it.m_pointData.size(), it.m_pointData.data(), &vec2d, &temp);

            if (isWithin)
                temp *= -1.f;

            temp -= 50.f;
            isWithin = temp < 0.f;

            if (temp < 0.f)
                temp *= -1.f;

            if (isWithin)
            {
                DNInfo::AddZoneLight(g_dnInfo, it.m_lightID, temp);
                
                break;
            }
        }
    }
}
