#pragma once

#include <Client/DBClient.hpp>

static DBClient* const g_ChrClassesDB = reinterpret_cast<DBClient*>(0xAD3404);
static DBClient* const g_mapDB = reinterpret_cast<DBClient*>(0xAD4160);
static DBClient* const g_spellDB = reinterpret_cast<DBClient*>(0xAD49D0);
