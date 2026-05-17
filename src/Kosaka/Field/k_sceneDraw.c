#include "Kosaka/Field/k_sceneDraw.h"
#include "Kosaka/Field/k_shadow.h"
#include "kwln/kwlnTask.h"
#include "Scene/mt_scene.h"
#include "Scene/resrcManager.h"
#include "rw/rwplcore.h"

// FUN_0019d410. 'draw opac field'
void* K_SceneDraw_UpdateDrwOpcFldTask(KwlnTask* drwOpcFld)
{
    // TODO
    
    return KWLNTASK_CONTINUE;
}

// FUN_0019d4a0. 'draw trans field'
void* K_SceneDraw_UpdateDrwTrnsFldTask(KwlnTask* drwTrnsFldTask)
{
    // TODO

    return KWLNTASK_CONTINUE;
}

// FUN_0019d530. 'draw trans field(sort)'
void* K_SceneDraw_UpdateDrwTrnsFldSrtTask(KwlnTask* drwTrnsFldSrtTask)
{
    // TODO

    return KWLNTASK_CONTINUE;
}

// FUN_0019d780. 'draw opac field object'
void* K_SceneDraw_UpdateDrwOpcFldObjTask(KwlnTask* drwOpcFldTask)
{
    // TODO
    
    return KWLNTASK_CONTINUE;
}

// FUN_0019de40. 'draw trans field object'
void* K_SceneDraw_UpdateDrwTrnsFldObjTask(KwlnTask* drwTrnsFldObjTask)
{
    // TODO

    return KWLNTASK_CONTINUE;
}

// FUN_0019e1b0. 'draw trans field obj preChar'
void* K_SceneDraw_UpdateDrwTrnsFldObjPCTask(KwlnTask* drwTrnsFldObjPCTask)
{
    // TODO

    return KWLNTASK_CONTINUE;
}

// FUN_0019e330. 'draw character model'
void* K_SceneDraw_UpdateDrwChrMdlTask(KwlnTask* drwChrMdlTask)
{
    // TODO

    return KWLNTASK_CONTINUE;
}

// FUN_0019ef80. 'draw trans NPC(sort)'
void* K_SceneDraw_UpdateDrwTrnsNpcSrtTask(KwlnTask* drwTrnsNpcSrtTask)
{
    // TODO

    return KWLNTASK_CONTINUE;
}

// FUN_0019f470. 'draw persona model'
void* K_SceneDraw_UpdateDrwPrsnaMdlTask(KwlnTask* drwPrsnaMdlTask)
{
    // TODO

    return KWLNTASK_CONTINUE;
}

// FUN_0019f730
KwlnTask* K_SceneDraw_CreateTasks(KwlnTask* rootProcTask)
{
    KwlnTask* sceneDrawTask;

    sceneDrawTask = kwlnTaskCreateWithAutoPriority(rootProcTask, 10, "scene draw CTL", NULL, NULL, NULL);

    FldShadow_CreateShadowMapTask(sceneDrawTask);
    kwlnTaskCreate(sceneDrawTask, "draw opac field", 2070, K_SceneDraw_UpdateDrwOpcFldTask, NULL, NULL);
    kwlnTaskCreate(sceneDrawTask, "draw opac field object", 2071, K_SceneDraw_UpdateDrwOpcFldObjTask, NULL, NULL);
    kwlnTaskCreate(sceneDrawTask, "draw character model", 2084, K_SceneDraw_UpdateDrwChrMdlTask, NULL, NULL);
    kwlnTaskCreate(sceneDrawTask, "draw trans field obj preChar", 2095, K_SceneDraw_UpdateDrwTrnsFldObjPCTask, NULL, NULL);
    kwlnTaskCreate(sceneDrawTask, "draw persona model", 4168, K_SceneDraw_UpdateDrwPrsnaMdlTask, NULL, NULL);
    kwlnTaskCreate(sceneDrawTask, "draw trans field object", 4172, K_SceneDraw_UpdateDrwTrnsFldObjTask, NULL, NULL);
    kwlnTaskCreate(sceneDrawTask, "draw trans field", 4173, K_SceneDraw_UpdateDrwTrnsFldTask, NULL, NULL);
    kwlnTaskCreate(sceneDrawTask, "draw trans field(sort)", 4183, K_SceneDraw_UpdateDrwTrnsFldSrtTask, NULL, NULL);
    kwlnTaskCreate(sceneDrawTask, "draw trans NPC(sort)", 4183, K_SceneDraw_UpdateDrwTrnsNpcSrtTask, NULL, NULL);

    return sceneDrawTask;
}

// FUN_0019fd40
RwRGBAReal* K_Scene_GetFldAmbLightColor()
{
    ResrcFld* res;

    res = (ResrcFld*)MT_Scene_GetResListHead(RESRC_TYPE_FLD);
    return &res->ambLightColor;
}

// FUN_001a0a10
RwRGBAReal* K_Scene_GetCharAmbLightColor()
{
    ResrcLightChar* res;

    res = (ResrcLightChar*)MT_Scene_GetResListHead(RESRC_TYPE_LIGHTCHAR);
    return &res->ambientColor;
}

// FUN_001a0250
u32 K_Scene_001a0250()
{
    s32 fldMajor;

    fldMajor = gMtScene->fldMajorId;

    if ((fldMajor >= 21 && fldMajor <= 28 && gMtScene->fldMinorId == 0) ||
        (fldMajor >= 41 && fldMajor <= 48 && gMtScene->fldMinorId == 0))
    {
        return true;
    }

    return false;
}