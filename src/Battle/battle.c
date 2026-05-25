#include "Battle/battle.h"
#include "kwln/kwlnTask.h"
#include "temporary.h"

static u64 sUID = 1; // 007cc510

Battle* gBtl; // 007ce3ec. NULL when not in a battle

// FUN_0027cb80
u64 btlGetUID()
{
    sUID++;

    if (sUID >= BTL_UIDMAX)
    {
        sUID = 1;
    }

    return sUID;
}

// FUN_0027d1d0
KwlnTask* btlStart(BtlStartInfo* startInfo)
{
    // TODO

    return NULL;
}

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