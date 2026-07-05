#include "Kosaka/Field/k_unit.h"
#include "Graphics/Model/mdlManager.h"
#include "Battle/battle.h"
#include "Main/g_data.h"
#include "Main/Battle/Data/datUnit.h"

FldUnitMdl gFldUnitsPcMdl[FLDUNIT_PC_MAX]; // 00871ea0
FldUnit gFldUnitsPc[FLDUNIT_PC_MAX];       // 008717a0

FldUnit gFldUnitsEc[FLDUNIT_EC_MAX];  // 0086eda0. Enemies
static u32 sFldUnitsEcCount;          // 007ce28c

// FUN_001cd870
void K_FldUnit_DestroyPcMdl(s32 unitId)
{
    if (gFldUnitsPcMdl[unitId].mdl != NULL)
    {
        mdlDestroy(gFldUnitsPcMdl[unitId].mdl);
        
        gFldUnitsPcMdl[unitId].mdl = NULL;
        gFldUnitsPcMdl[unitId].type = 0;
        gFldUnitsPcMdl[unitId].id = 0;
    }
}

// FUN_001cd940
FldUnit* K_FldUnit_FindFreePc()
{
    FldUnit* units;
    FldUnit* free;
    FldUnit* curr;
    s32 i;

    free = NULL;
    i = 0;
    units = gFldUnitsPc;
    for (; i < FLDUNIT_PC_MAX; i++)
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

// FUN_001cfc50
FldUnit* K_FldUnit_CreateReaper(u32 unused, const RwV3d* spawnPos)
{
    FldUnit* units;
    FldUnit* curr;
    FldUnit* unit;
    s32 i;

    unit = NULL;
    i = 0;
    units = gFldUnitsEc;
    for (; i < FLDUNIT_EC_MAX; i++)
    {
        curr = &units[i];
        if (curr->genusBase == NULL)
        {
            unit = curr;
            break;
        }
    }

    if (datGetFlag(5141) == true)
    {
        return NULL;
    }
    else if (unit == NULL)
    {
        return NULL;
    }

    unit->genusBase = (DatUnitGenusBase*)datUnitCreateEc(BTLENCOUNT_REAPER);
    unit->encount = &gEncountTbl[BTLENCOUNT_REAPER];
    unit->unk_18c = 4;
    unit->scaleIdx = 0;
    unit->charId = 0;
    unit->mdl = mdlCreateAndResolvePath(MODEL_TYPE_ENEMYSYMBOL, 3, MDL_READASYNC);
    unit->spawnPos = *spawnPos;
    unit->unk_168 = &unit->unk_58;
    unit->xGrid = (spawnPos->x + 400.0f) / 800.0f;
    unit->zGrid = (spawnPos->z + 400.0f) / 800.0f;
    unit->unk_184 = 1000;

    sFldUnitsEcCount++;

    return unit;
}

// FUN_001d0110
void K_FldUnit_Destroy(FldUnit* unit)
{
    // TODO
}

// FUN_001d0330
void K_FldUnit_DestroyAllPc()
{
    s32 i;

    for (i = 0; i < FLDUNIT_PC_MAX; i++)
    {
        K_FldUnit_Destroy(&gFldUnitsPc[i]);
    }
}

// FUN_001d0390
void K_FldUnit_DestroyAllEc()
{
    s32 i;

    for (i = 0; i < FLDUNIT_EC_MAX; i++)
    {
        K_FldUnit_Destroy(&gFldUnitsEc[i]);
    }
}