#pragma once
#include "../SharedDefines.h"

struct CustomDBC
{
	void* rows;
	uint32_t numRows;
	int32_t minIndex;
	int32_t maxIndex;
	void* stringTable;
};

static std::unordered_map<std::string, CustomDBC> allCDBCs;

class CDBC
{
public:
	CDBC()
	{
		numColumns = 0;
		rowSize = 0;
	}

	void LoadDB(const char* filename);
	void UnloadDB(const char* filename);
	int32_t GetMinIndex(const char* filename);
	int32_t GetMaxIndex(const char* filename);
	uint32_t GetNumRows(const char* filename);
	virtual ~CDBC() = default;

	virtual void* GetRow(const char* filename, int32_t index) { return nullptr; }
protected:
	uint32_t numColumns;
	uint32_t rowSize;
};
