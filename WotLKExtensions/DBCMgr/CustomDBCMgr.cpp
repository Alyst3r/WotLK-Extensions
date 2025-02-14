#include "CustomDBCMgr.h"
#include "Defs/SpellCustomAttributes.h"

CustomDBCMgr GlobalDBCMap;

void CustomDBCMgr::addDBC(std::string dbcName)
{
    allCustomDBCs[dbcName] = CustomDBC();
}

void CustomDBCMgr::Load()
{
    if (useSpellCustomAttrDBC)
        SpellCustomAttributes().LoadDB();
}
