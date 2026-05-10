#include "Kosaka/Field/k_unit.h"
#include "Model/mdlManager.h"

FldUnitMdl gFldUnitsMdl[FLDUNIT_MAX]; // 00871ea0
FldUnit gFldUnits[FLDUNIT_MAX];       // 008717a0

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