#include "Event/Comu/comuFunction.h"

static SiteibiEventTable sSiteibiEvtTable; // 0095b658

SiteibiEventTable* Comu_GetSiteibiEvtTable()
{
    return &sSiteibiEvtTable;
}