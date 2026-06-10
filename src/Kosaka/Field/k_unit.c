#include "Kosaka/Field/k_unit.h"
#include "Model/mdlManager.h"

FldUnitMdl gFldUnitsMdl[FLDUNIT_MAX]; // 00871ea0
FldUnit gFldUnits[FLDUNIT_MAX];       // 008717a0

FldUnit gEnFldUnits[FLDUNIT_EN_MAX];  // 0086eda0. Enemies

// FUN_001cd870
void K_FldUnit_DestroyMdl(s32 unitId)
{
    if (gFldUnitsMdl[unitId].mdl != NULL)
    {
        mdlDestroy(gFldUnitsMdl[unitId].mdl);
        
        gFldUnitsMdl[unitId].mdl = NULL;
        gFldUnitsMdl[unitId].type = 0;
        gFldUnitsMdl[unitId].id = 0;
    }
}

// FUN_001cd940
FldUnit* K_FldUnit_FindFree()
{
    FldUnit* units;
    FldUnit* free;
    FldUnit* curr;
    s32 i;

    free = NULL;
    i = 0;
    units = gFldUnits;
    for (; i < FLDUNIT_MAX; i++)
    {
        curr = &units[i];
        if (curr->genusBase == NULL)
        {
            free = curr;
            break;
        }
    }

    return free;
}