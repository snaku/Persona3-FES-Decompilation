#include "Battle/battle.h"
#include "Battle/btlFade.h"
#include "kwln/kwlnTask.h"
#include "Scene/mt_scene.h"
#include "Scene/resrcManager.h"
#include "Script/scrTraceCode.h"
#include "admini.h"
#include "g_data.h"
#include "temporary.h"

#define BTL_CHAR_RESID_BASE 0x100
#define BTL_CHAR_RESID_MAX  0x200

static u64 sUID = 1;                             // 007cc510
static u16 sCurrCharResId = BTL_CHAR_RESID_BASE; // 007cc518

BtlEncountTable* gEncountTbl; // 007ce4a8
Battle* gBtl;                 // 007ce3ec. NULL when not in a battle

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

// FUN_0027d5e0
u32 btlScrCmd_CALL_BATTLE()
{
    BtlEncountTable* encount;
    BtlStartInfo startInfo;
    u16 i;
    u16 currCharId;
    u16 encountId;

    btlFadeCreateTask(1);

    encountId = scrGetIntPara(0);
    encount = &gEncountTbl[encountId];

    memset(&startInfo, 0, sizeof(BtlStartInfo));

    startInfo.partyUnits[0] = datUnitCreatePlayer(CHARACTER_HERO);
    for (i = 0; i < 4; i++)
    {
        currCharId = datGetPartyId(i);
        if (currCharId != CHARACTER_NONE)
        {
            startInfo.partyUnits[i + 1] = datUnitCreatePlayer(currCharId);
        }
    }

    startInfo.enmUnits = datUnitCreateEnemy(encountId);
    
    if (encount->fldMajorId == 0 && encount->fldMinorId == 0)
    {
        startInfo.fldMajorId = 221;
        startInfo.fldMinorId = 1;
    }
    else
    {
        startInfo.fldMajorId = encount->fldMajorId;
        startInfo.fldMinorId = encount->fldMinorId;
    }

    adminiChangeSeq(ADMINI_SEQ_BATTLE, &startInfo, sizeof(BtlStartInfo), false);

    return true;
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
void btl0027d8b0()
{
    gBtl->flags |= BTL_FLAG_UNK8000;
}