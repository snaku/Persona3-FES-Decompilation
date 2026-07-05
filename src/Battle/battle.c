#include "Battle/battle.h"
#include "Battle/btlFade.h"
#include "Kosaka/k_data.h"
#include "Kosaka/k_misc.h"
#include "Kernel/Kwln/kwlnTask.h"
#include "Scene/mt_scene.h"
#include "Scene/resrcManager.h"
#include "Script/scrTraceCode.h"
#include "Script/scrScriptProcess.h"
#include "Yajima/y_timeLimit.h"
#include "Main/Battle/Data/datCalc.h"
#include "Main/Battle/Panel/bp_root.h"
#include "Main/admini.h"
#include "Main/g_data.h"
#include "g_flags.h"
#include "temporary.h"

#define BTL_CHAR_RESID_BASE 0x100
#define BTL_CHAR_RESID_MAX  0x200

static u64 sUID = 1;                             // 007cc510
static u16 sCurrCharResId = BTL_CHAR_RESID_BASE; // 007cc518

BtlEncountTable* gEncountTbl; // 007ce4a8
static u32 sIsDead;           // 007ce3f0
Battle* gBtl;                 // 007ce3ec. NULL when not in a battle

u32 btlDestroy();

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

// FUN_0027cc30
void* btlUpdateTask(KwlnTask* btlTask)
{
    // TODO

    return KWLNTASK_CONTINUE;
}

// FUN_0027ccf0
void* btlUpdateDraw3DTask(KwlnTask* btlDraw3DTask)
{
    // TODO

    return KWLNTASK_CONTINUE;
}

// FUN_0027cd70
void* btlUpdateDraw3DFrontTask(KwlnTask* btlDraw3DFrontTask)
{
    // TODO

    return KWLNTASK_CONTINUE;
}

// FUN_0027cda0
void* btlUpdateDraw2DTask(KwlnTask* btlDraw2DTask)
{
    // TODO

    return KWLNTASK_CONTINUE;
}

// FUN_0027cdf0
void btlDestroyTask(KwlnTask* btlTask)
{
    btlDestroy();
}

// FUN_0027ced0
void btlCreate()
{
    // TODO
}

// FUN_0027d020
u32 btlDestroy()
{
    // TODO

    return false;
}

// FUN_0027ce10
void btlStop()
{
    if (kwlnTaskGetTaskByName("battle") != NULL)
    {
        kwlnTaskDestroyWithHierarchy(gBtl->btlTask);
    }
}

// FUN_0027d1d0
KwlnTask* btlStart(BtlStartInfo* startInfo)
{
    KwlnTask* btlTask;

    btlCreate();

    gBtl->btlTask = kwlnTaskCreate(NULL,
                                   "battle",
                                   10,
                                   btlUpdateTask,
                                   btlDestroyTask,
                                   NULL);

    kwlnTaskCreate(gBtl->btlTask,
                   "battle_draw_3d",
                   2081,
                   btlUpdateDraw3DTask,
                   NULL,
                   NULL);
    kwlnTaskCreate(gBtl->btlTask,
                   "battle_draw_3d_front",
                   4169,
                   btlUpdateDraw3DFrontTask,
                   NULL,
                   NULL);
    kwlnTaskCreate(gBtl->btlTask,
                   "battle_draw_2d",
                   4207,
                   btlUpdateDraw2DTask,
                   NULL,
                   NULL);

    gBtl->btlPanelTask = bpRootCreateTasks(gBtl->btlTask);
    bpRoot001ff350();

    btlTask = gBtl->btlTask;

    if (startInfo != NULL)
    {
        gBtl->hasNoStartInfo = false;

        memcpy(&gBtl->startInfo, startInfo, sizeof(BtlStartInfo));

        gBtl->fldMajorId = gBtl->startInfo.fldMajorId;
        gBtl->fldMinorId = gBtl->startInfo.fldMinorId;

        btlMainSetState(BTL_STATE_INIT);
    }
    else
    {
        gBtl->hasNoStartInfo = true;

        if (!datGetFlag(FLG_BATTLE_MC))
        {
            btlMainSetState(BTL_STATE_TEST);
        }
        else
        {
            btlMainSetState(BTL_STATE_MC);
        }
    }

    gBtl->flags |= BTL_FLAG_ACTIVE;

    return btlTask;
}

// FUN_0027d5e0
u32 btlScrCmd_CALL_BATTLE()
{
    BtlEncountTable* encount;
    BtlStartInfo startInfo;
    u16 i;
    u16 currPcId;
    u16 encountId;

    btlFadeCreateTask(1);

    encountId = scrGetIntPara(0);
    encount = &gEncountTbl[encountId];

    memset(&startInfo, 0, sizeof(BtlStartInfo));

    startInfo.partyUnits[0] = datUnitCreatePc(PC_HERO);
    for (i = 0; i < 4; i++)
    {
        currPcId = datGetPartyId(i);
        if (currPcId != PC_NONE)
        {
            startInfo.partyUnits[i + 1] = datUnitCreatePc(currPcId);
        }
    }

    startInfo.enmUnits = datUnitCreateEc(encountId);
    
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

// FUN_0027d730
u32 btlScrCmd_CHK_HERO_DIED_TARTAROS()
{
    if (scrGetIntPara(0) > 10) // ?
    {
        if (gBtl != NULL)
        {
            sIsDead = false;
            return false;
        }

        if (!sIsDead)
        {
            if (datCalcIsDead(datGetUnit(PC_HERO), 0))
            {
                datSetFlag(FLG_HERO_DIED, true);

                Y_TimeLimit_0045a400();

                // TODO: lw a2, %gp_rel(gFldScrSize) before other args
                scrCreateTaskFromScriptMemory(10, gFldScrMemory, gFldScrSize, FLDSCR_DIED_IN_TARTAROS);
                K_Misc_CreateScrShutdownTask(scrGetCurrent()->task);

                sIsDead = true;
            }
            else
            {
                return true;
            }
        }
    }

    return false;
}

// FUN_0027d810
u32 btlScrCommand_ENCOUNT_FADE()
{
    btlFadeCreateTask(1);

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

// FUN_0027dbe0
u32 btlUpdateSetFlagsPacket(void* work)
{
    BtlBattleFlagPacket* packet;

    packet = (BtlBattleFlagPacket*)work;

    gBtl->flags |= packet->flags;

    return true;
}

// FUN_0027dc00
BtlPacket* btlCreateSetFlagsPacket(u32 flags)
{
    BtlPacket* packet;

    packet = btlPacketCreate(BTLBATTLE_PACKET_SETFLAGS, sizeof(BtlBattleFlagPacket));

    packet->updateFunc = btlUpdateSetFlagsPacket;

    ((BtlBattleFlagPacket*)packet->workData)->flags = flags;

    return packet;
}