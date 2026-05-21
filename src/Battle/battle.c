#include "Battle/battle.h"
#include "kwln/kwlnTask.h"
#include "temporary.h"

Battle* gBtl; // 007ce3ec. NULL when not in a battle

// FUN_0027d880
KwlnTask* btlGetTask()
{
    if (gBtl == NULL)
    {
        return NULL;
    }

    return gBtl->btlTask;
}

// FUN_0027d8b0
void btlSetIsBoss()
{
    gBtl->flags |= BTL_FLAG_IS_BOSS;
}