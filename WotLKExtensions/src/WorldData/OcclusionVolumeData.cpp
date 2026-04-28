#include <Data/Structs.hpp>
#include <Misc/DataContainer.hpp>
#include <Misc/Util.hpp>
#include <WorldData/OcclusionVolumeData.hpp>

void OcclusionVolumeData::ApplyOcclusionVolumeExtensions()
{
    //Util::OverwriteUInt32AtAddress(0x7CCD30, reinterpret_cast<uint32_t>(&sDC.GetOcclusionVolumeData()->m_min));
    //Util::OverwriteUInt32AtAddress(0x7CCD35, sDC.GetOcclusionVolumeDataSize());
    Util::OverwriteUInt32AtAddress(0x7CD8A0, reinterpret_cast<uint32_t>(&sDC.GetOcclusionVolumeData()->m_flags));
    Util::OverwriteUInt32AtAddress(0x7CD8A5, sDC.GetOcclusionVolumeDataSize());
    Util::OverwriteUInt32AtAddress(0x7CDC16, reinterpret_cast<uint32_t>(&sDC.GetOcclusionVolumeData()->m_pointData));
    Util::OverwriteUInt32AtAddress(0x7CDC1D, sDC.GetOcclusionVolumeDataSize());
    Util::OverwriteUInt32AtAddress(0x7CDD23, reinterpret_cast<uint32_t>(sDC.GetOcclusionVolumeData()));
    Util::OverwriteUInt32AtAddress(0x7CDD2D, sDC.GetOcclusionVolumeDataSize());

    // skip calling sub_7CCD20, it's already done in FillOcclusionVolumeData
    *reinterpret_cast<uint32_t*>(0xD2DCD4) = 1;
}

void OcclusionVolumeData::FillOcclusionVolumeData()
{
    for (uint32_t i = sDC.GetOcclusionVolumeRowMinIndex(); i <= sDC.GetOcclusionVolumeRowMaxIndex(); i++)
    {
        OcclusionVolumeData data{};
        OcclusionVolumeRow row{};
        std::vector<C3Vector> points;

        sDC.GetOcclusionVolumeRow(row, i);

        if (row.m_ID <= -1)
            continue;

        data.m_mapID = row.m_mapID;
        data.m_flags = row.m_flags;

        for (uint32_t j = 1; j <= sDC.GetOcclusionVolumePointRowMaxIndex(); j++)
        {
            OcclusionVolumePointRow tempRow{};
            C3Vector tempVec{};

            sDC.GetOcclusionVolumePointRow(tempRow, j);

            if (tempRow.m_ID <= -1 || tempRow.m_occlusionVolumeID < row.m_ID)
                continue;

            if (tempRow.m_occlusionVolumeID > row.m_ID)
                break;

            tempVec.m_x = tempRow.m_positionX;
            tempVec.m_y = tempRow.m_positionY;
            tempVec.m_z = tempRow.m_positionZ;

            points.push_back(tempVec);

            if (j == sDC.GetOcclusionVolumePointRowMinIndex())
            {
                data.m_min = tempVec;
                data.m_max = tempVec;
            }

            if (data.m_min.m_x > tempVec.m_x)
                data.m_min.m_x = tempVec.m_x;

            if (data.m_min.m_y > tempVec.m_y)
                data.m_min.m_y = tempVec.m_y;

            if (data.m_min.m_z > tempVec.m_z)
                data.m_min.m_z = tempVec.m_z;

            if (data.m_max.m_x < tempVec.m_x)
                data.m_max.m_x = tempVec.m_x;

            if (data.m_max.m_y < tempVec.m_y)
                data.m_max.m_y = tempVec.m_y;

            if (data.m_max.m_z < tempVec.m_z)
                data.m_max.m_z = tempVec.m_z;
        }

        if (points.size())
        {
            data.m_pointData = malloc(points.size() * sizeof(C3Vector));
            data.m_pointCount = points.size();

            memcpy(data.m_pointData, points.data(), points.size() * sizeof(C3Vector));
        }

        sDC.AddOcclusionVolume(data);
    }
}
