#pragma once

#include "SharedDefines.h"

static std::vector<ZoneLightData> GlobalZoneLightData;

class WorldDataExtensions
{
public:
	static void ApplyPatches();
private:
	static void ApplyZoneLightsExtensions();
	static void FillZoneLightData();
	static void FindAndAddZoneLightEx(C3Vector* vec);

};
