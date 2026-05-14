#pragma once

class DBCReloader {
public:
	static int LoadAllDBCs();
	static int ReloadDBCByName(const char* name);
};