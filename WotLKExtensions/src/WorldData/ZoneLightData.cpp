#include <CDBCMgr/CDBCDefs/ZoneLight.hpp>
#include <CDBCMgr/CDBCDefs/ZoneLightPoint.hpp>
#include <Data/Structs.hpp>
#include <Misc/DataContainer.hpp>
#include <Misc/Util.hpp>
#include <WorldData/DNInfo.hpp>
#include <WorldData/ZoneLightData.hpp>

void ZoneLightData::ApplyZoneLightsExtensions()
{
    Util::OverwriteUInt32AtAddress(0x781426, reinterpret_cast<uint32_t>(&FillZoneLightData) - 0x78142A);
    // sets the check for map id to > -1 so it's always true unless no map is loaded
    Util::OverwriteUInt32AtAddress(0x781730, 0xFFFFFFFF);
    Util::OverwriteUInt32AtAddress(0x781751, reinterpret_cast<uint32_t>(&FindAndAddZoneLightEx) - 0x781755);
    // calls nullsub_3 instead of original function
    Util::OverwriteUInt32AtAddress(0x9E0360, 0x5EEB70);
}

void ZoneLightData::FillZoneLightData()
{
    for (uint32_t i = sDC.GetZoneLightRowMinIndex(); i <= sDC.GetZoneLightRowMaxIndex(); i++)
    {
        ZoneLightData data{};
        ZoneLightRow row{};
        std::vector<C2Vector> points;

        sDC.GetZoneLightRow(row, i);

        if (row.m_ID <= -1)
            continue;

        data.m_mapID = row.m_mapID;
        data.m_lightID = row.m_lightID;

        for (uint32_t j = 1; j <= sDC.GetZoneLightPointRowMaxIndex(); j++)
        {
            ZoneLightPointRow tempRow{};
            C2Vector tempVec{};

            sDC.GetZoneLightPointRow(tempRow, j);

            if (tempRow.m_ID <= -1 || tempRow.m_zoneLightID < row.m_ID)
                continue;

            if (tempRow.m_zoneLightID > row.m_ID)
                break;

            tempVec.m_x = tempRow.m_positionX;
            tempVec.m_y = tempRow.m_positionY;

            points.push_back(tempVec);

            if (j == sDC.GetZoneLightPointRowMinIndex())
            {
                data.m_min = tempVec;
                data.m_max = tempVec;
            }

            if (data.m_min.m_x > tempVec.m_x)
                data.m_min.m_x = tempVec.m_x;

            if (data.m_min.m_y > tempVec.m_y)
                data.m_min.m_y = tempVec.m_y;

            if (data.m_max.m_x < tempVec.m_x)
                data.m_max.m_x = tempVec.m_x;

            if (data.m_max.m_y < tempVec.m_y)
                data.m_max.m_y = tempVec.m_y;

            if (points.size())
                data.m_pointData = points;
        }

        data.m_min.m_x -= 50.f;
        data.m_min.m_y -= 50.f;
        data.m_max.m_x += 50.f;
        data.m_max.m_y += 50.f;

        sDC.AddZoneLight(data);
    }
}

void ZoneLightData::FindAndAddZoneLightEx(C3Vector* vec)
{
    auto& zoneLightData = sDC.GetZoneLightData();
    void* g_dnInfo = DNInfo::GetDNInfoPtr();
    int32_t currentMap = *reinterpret_cast<int32_t*>(0xADFBC4);
    C2Vector vec2d{ -(vec->m_y - 17066.666f), -(vec->m_x - 17066.666f) };

    if (!zoneLightData.size())
        return;

    for (auto& it : zoneLightData)
    {
        if (it.m_mapID == currentMap && it.m_min.m_x <= vec2d.m_x && it.m_min.m_y <= vec2d.m_y && it.m_max.m_x >= vec2d.m_x && it.m_max.m_y >= vec2d.m_y)
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
