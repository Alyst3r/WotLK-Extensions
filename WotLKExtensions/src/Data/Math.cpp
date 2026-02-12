#include <Data/Math.hpp>

bool NTempest::DistanceSquaredFromEdge(int32_t index, void* data, C2Vector* vec, float* f)
{
	return reinterpret_cast<bool (__cdecl*)(int32_t, void*, C2Vector*, float*)>(0x7F9C90)(index, data, vec, f);
}
