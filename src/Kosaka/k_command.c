#include "Kosaka/k_command.h"
#include "Kosaka/k_assert.h"
#include "Kosaka/Field/k_dungeon.h"
#include "Kosaka/Field/k_field.h"
#include "Script/scrTraceCode.h"
#include "Model/mdlManager.h"
#include "Scene/resrcManager.h"
#include "Scene/mt_scene.h"
#include "datCalendar.h"
#include "g_data.h"
#include "h_snd.h"
#include "temporary.h"

// FUN_001c2480
u8 K_Cmd_SKIP_TO_DARK_HOUR()
{
    if (K_Field_Get()->rootTask != NULL)
    {
        datSetTimeSkipTarget(CALENDAR_TIME_DARK_HOUR);
        datSetSkipToTarget(true);
        datSetDaysSkipTarget(datGetDaysSinceApr5());

        K_Field_SetShouldShutdown(K_Field_Get()->rootTask, true);

        clndReqSkip();
    }

    return true;
}

// FUN_001c2550
u8 K_Cmd_REQ_CLND_SKIP()
{
    clndReqSkip();

    return true;
}

// FUN_001c26c0
u8 K_Cmd_GET_MONTH()
{
    scrSetIntReturnVal(clndGetCurrentMonth());

    return true;
}

// FUN_001c26f0
u8 K_Cmd_GET_DAY()
{
    scrSetIntReturnVal(clndGetCurrentDay());

    return true;
}

// FUN_001c2720
u8 K_Cmd_GET_DAY_OF_WEEK()
{
    scrSetIntReturnVal(clndGetCurrentWeekDay());

    return true;
}

// FUN_001c2750
u8 K_Cmd_GET_TIME()
{
    scrSetIntReturnVal(datGetTime());

    return true;
}

// FUN_001c2780
u8 K_Cmd_DATE_IN_RANGE()
{
    u32 startMonth;
    u32 startDay;
    u32 endMonth;
    u32 endDay;

    startMonth = scrGetIntPara(0);
    startDay = scrGetIntPara(1);
    endMonth = scrGetIntPara(2);
    endDay = scrGetIntPara(3);

    if (clndIsDateInRange(startMonth, startDay, endMonth, endDay))
    {
        scrSetIntReturnVal(1);
    }
    else
    {
        scrSetIntReturnVal(0);
    }

    return true;
}

// FUN_001c2900
u8 K_Cmd_RESRC_MDL_ANIM()
{
    s32 resTypeId;
    s32 animId;
    s32 shouldLoop;
    s32 blendFrameCount;
    f32 animSpeed;
    ResrcModelParty* party;
    ResrcModelNpc* npc;
    ResrcModelFld* fld;

    resTypeId = scrGetIntPara(0);
    animId = scrGetIntPara(1);
    shouldLoop = scrGetIntPara(2);
    blendFrameCount = scrGetFloatPara(3); // this shouldn't be scrGetFloatPara
    animSpeed = scrGetFloatPara(4);

    switch (RESRC_GET_TYPE(resTypeId))
    {
        case RESRC_TYPE_MODELPARTY:
            party = (ResrcModelParty*)MT_Scene_GetRes(resTypeId);
            if (party != NULL)
            {
                if (shouldLoop)
                {
                    mdlAnimSet(party->mdl, 0, animId, blendFrameCount, MDLANIM_FLAG_LOOP);
                }
                else
                {
                    mdlAnimSet(party->mdl, 0, animId, blendFrameCount, 0);
                }

                mdlAnimSetSpeed(party->mdl, 0, animSpeed);
            }
            break;
            
        case RESRC_TYPE_MODELNPC:
            npc = (ResrcModelNpc*)MT_Scene_GetRes(resTypeId);
            if (npc != NULL)
            {
                if (shouldLoop)
                {
                    mdlAnimSet(npc->mdl, 0, animId, blendFrameCount, MDLANIM_FLAG_LOOP);
                }
                else
                {
                    mdlAnimSet(npc->mdl, 0, animId, blendFrameCount, 0);
                }

                mdlAnimSetSpeed(npc->mdl, 0, animSpeed);
            }
            break;

        case RESRC_TYPE_MODELFLD:
            fld = (ResrcModelFld*)MT_Scene_GetRes(resTypeId);
            if (fld != NULL)
            {
                if (shouldLoop)
                {
                    mdlAnimSet(fld->mdl, 0, animId, blendFrameCount, MDLANIM_FLAG_LOOP);
                }
                else
                {
                    mdlAnimSet(fld->mdl, 0, animId, blendFrameCount, 0);
                }

                mdlAnimSetSpeed(fld->mdl, 0, animSpeed);
            }
            break;
        
        default: K_Assert("k_command.c", 527);
    }

    return true;
}

// FUN_001c2b80
u8 K_Cmd_RESRC_MDL_ANIM_SYNC()
{
    u32 resTypeId;
    Resrc* res;

    resTypeId = scrGetIntPara(0);
    switch (RESRC_GET_TYPE(resTypeId))
    {
        case RESRC_TYPE_MODELPARTY:
            res = MT_Scene_GetRes(resTypeId);
            if (res != NULL)
            {
                return ((ResrcModelParty*)res)->mdl->animSlots[0].anim.isAnimEnd == true;
            }
            break;
            
        case RESRC_TYPE_MODELNPC:
            res = MT_Scene_GetRes(resTypeId);
            if (res != NULL)
            {
                return ((ResrcModelNpc*)res)->mdl->animSlots[0].anim.isAnimEnd == true;
            }
            break;

        case RESRC_TYPE_MODELFLD:
            res = MT_Scene_GetRes(resTypeId);
            if (res != NULL)
            {
                return ((ResrcModelFld*)res)->mdl->animSlots[0].anim.isAnimEnd == true;
            }
            break;
        
        default: K_Assert("k_command.c", 577);
    }

    return true;
}

// FUN_001c2c80
u8 K_Cmd_RESRC_MODEL_SCALE()
{
    u32 resTypeId;
    RwV3d scale;
    Resrc* res;

    resTypeId = scrGetIntPara(0);
    scale.x = scrGetFloatPara(1);
    scale.y = scrGetFloatPara(1);
    scale.z = scrGetFloatPara(1);

    switch (RESRC_GET_TYPE(resTypeId))
    {
        case RESRC_TYPE_MODELPARTY:
            res = MT_Scene_GetRes(resTypeId);
            if (res != NULL)
            {
                mdlScale(((ResrcModelParty*)res)->mdl, &scale, rwCOMBINEPOSTCONCAT);
            }
            break;
        
        case RESRC_TYPE_MODELNPC:
            res = MT_Scene_GetRes(resTypeId);
            if (res != NULL)
            {
                mdlScale(((ResrcModelNpc*)res)->mdl, &scale, rwCOMBINEPOSTCONCAT);
            }
            break;
        
        case RESRC_TYPE_MODELFLD:
            res = MT_Scene_GetRes(resTypeId);
            if (res != NULL)
            {
                mdlScale(((ResrcModelFld*)res)->mdl, &scale, rwCOMBINEPOSTCONCAT);
            }
            break;

        default: K_Assert("k_command.c", 623);
    }

    return true;
}

// FUN_001c2ea0
u8 K_Cmd_GET_DUNGEON_FLOOR()
{
    scrSetIntReturnVal(K_FldDungeon_GetCurrentFloor());

    return true;
}

// FUN_001c45e0
u8 K_Cmd_CREATE_FLD_MDL()
{
    char path[64];
    char buff[64];
    s32 majorId;
    u32 minorId;
    Model* mdl;

    majorId = scrGetIntPara(0);
    minorId = scrGetIntPara(1);

    if (majorId > -1)
    {
        strcpy(path, "field/rmd/m");

        sprintf(buff, "%03d_", majorId);
        strcat(path, buff);

        sprintf(buff, "%03d.RMD", minorId);
        strcat(path, buff);
    }
    else
    {
        strcpy(path, "field/grmd/fobj");
        sprintf(buff, "%03d.RMD", minorId);
        strcat(path, buff);
    }

    mdl = mdlMngCreateMdlFromPath(MODEL_TYPE_FLD,
                                  minorId,
                                  path,
                                  MDL_READASYNC);
    scrSetIntReturnVal((s32)mdl);

    return true;
}

// FUN_001c4a00
u8 K_Cmd_CREATE_MDL()
{
    s32 type;
    s32 id;
    Model* mdl;

    type = scrGetIntPara(0);
    id = scrGetIntPara(1);

    mdl = mdlMngCreateMdlAndResolvePath(type, id, MDL_READASYNC);

    scrSetIntReturnVal((s32)mdl);

    return true;
}

// FUN_001c54a0
u8 K_Cmd_PLAY_BGM()
{
    s16 currBgm;
    s32 reqBgm;

    currBgm = H_Snd_GetCurrentBgmId();

    if (currBgm != scrGetIntPara(0))
    {
        H_Snd_PlayBgm(scrGetIntPara(0), 1);
    }

    return true;
}

// FUN_001c56a0
u8 K_Cmd_GET_NPC_NO()
{
    ResrcModelNpc* npc;
    s32 no;

    npc = (ResrcModelNpc*)MT_Scene_GetResListHead(RESRC_TYPE_MODELNPC);
    no = 0;
    while (npc != NULL)
    {
        no++;
        npc = (ResrcModelNpc*)npc->base.next;
    }

    scrSetIntReturnVal(no);

    return true;
}

// FUN_001c5e60
u8 K_Cmd_CHK_SCENARIO_ANSWER()
{
    s32 isAnswer;

    isAnswer = false;
    if (datGetScenarioMode() == SCENARIO_MODE_ANSWER)
    {
        isAnswer = true;
    }

    scrSetIntReturnVal(isAnswer);

    return true;
}