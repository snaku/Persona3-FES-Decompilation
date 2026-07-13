#include "Main/Battle/Data/datScript.h"
#include "Main/Battle/Data/datUnit.h"
#include "Kosaka/k_assert.h"

static DatScriptWork sWork;

static ScrData* sUnk_007ce514; // doesn't looks like it's used

// FUN_003111f0
u32 datScriptIsNotEnemy()
{
    K_ASSERT(sWork.currUnit != NULL, 517);

    return !(sWork.currUnit->flags & UNIT_FLAG_ENEMY);
}

// FUN_003112c0
u32 datScript003112c0(ScrData* scr)
{
    return sUnk_007ce514 == scr;
}