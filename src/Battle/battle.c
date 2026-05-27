#include "Battle/battle.h"
#include "kwln/kwlnTask.h"
#include "Scene/mt_scene.h"
#include "Scene/resrcManager.h"
#include "temporary.h"

#define BTL_CHAR_RESID_BASE 0x100
#define BTL_CHAR_RESID_MAX  0x200

static u64 sUID = 1;                             // 007cc510
static u16 sCurrCharResId = BTL_CHAR_RESID_BASE; // 007cc518

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

// FUN_0027cbd0
u16 btlFindFreeCharResId()
{
    do
    {
        if (++sCurrCharResId >= BTL_CHAR_RESID_MAX)
        {
            sCurrCharResId = BTL_CHAR_RESID_BASE;
        }
    } while (MT_Scene_GetRes(RESRC_MAKE_TYPEID(sCurrCharResId, RESRC_TYPE_MODELCHAR)) != NULL);

    return sCurrCharResId;
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