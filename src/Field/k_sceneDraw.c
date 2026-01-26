#include "kwln/kwlnTask.h"
#include "Field/k_sceneDraw.h"
#include "Field/k_shadow.h"

// FUN_0019d410. 'draw opac field'
s32 FldSceneDraw_UpdateDrwOpcFldTask(KwlnTask* drwOpcFld)
{
    // TODO
    
    return KWLN_TASK_CONTINUE;
}

// FUN_0019d4a0. 'draw trans field'
s32 FldSceneDraw_UpdateDrwTrnsFldTask(KwlnTask* drwTrnsFldTask)
{
    // TODO

    return KWLN_TASK_CONTINUE;
}

// FUN_0019d530. 'draw trans field(sort)'
s32 FldSceneDraw_UpdateDrwTrnsFldSrtTask(KwlnTask* drwTrnsFldSrtTask)
{
    // TODO

    return KWLN_TASK_CONTINUE;
}

// FUN_0019d780. 'draw opac field object'
s32 FldSceneDraw_UpdateDrwOpcFldObjTask(KwlnTask* drwOpcFldTask)
{
    // TODO
    
    return KWLN_TASK_CONTINUE;
}

// FUN_0019de40. 'draw trans field object'
s32 FldSceneDraw_UpdateDrwTrnsFldObjTask(KwlnTask* drwTrnsFldObjTask)
{
    // TODO

    return KWLN_TASK_CONTINUE;
}

// FUN_0019e1b0. 'draw trans field obj preChar'
s32 FldSceneDraw_UpdateDrwTrnsFldObjPCTask(KwlnTask* drwTrnsFldObjPCTask)
{
    // TODO

    return KWLN_TASK_CONTINUE;
}

// FUN_0019e330. 'draw character model'
s32 FldSceneDraw_UpdateDrwChrMdlTask(KwlnTask* drwChrMdlTask)
{
    // TODO

    return KWLN_TASK_CONTINUE;
}

// FUN_0019ef80. 'draw trans NPC(sort)'
s32 FldSceneDraw_UpdateDrwTrnsNpcSrtTask(KwlnTask* drwTrnsNpcSrtTask)
{
    // TODO

    return KWLN_TASK_CONTINUE;
}

// FUN_0019f470. 'draw persona model'
s32 FldSceneDraw_UpdateDrwPrsnaMdlTask(KwlnTask* drwPrsnaMdlTask)
{
    // TODO

    return KWLN_TASK_CONTINUE;
}

// FUN_0019f730
KwlnTask* FldSceneDraw_CreateTasks(KwlnTask* rootProcTask)
{
    KwlnTask* fldSceneDrawTask;

    fldSceneDrawTask = KwlnTask_CreateWithAutoPriority(rootProcTask, 10, "scene draw CTL", NULL, NULL, NULL);

    FldShadow_CreateShadowMapTask(fldSceneDrawTask);
    KwlnTask_Create(fldSceneDrawTask, "draw opac field", 2070, FldSceneDraw_UpdateDrwOpcFldTask, NULL, NULL);
    KwlnTask_Create(fldSceneDrawTask, "draw opac field object", 2071, FldSceneDraw_UpdateDrwOpcFldObjTask, NULL, NULL);
    KwlnTask_Create(fldSceneDrawTask, "draw character model", 2084, FldSceneDraw_UpdateDrwChrMdlTask, NULL, NULL);
    KwlnTask_Create(fldSceneDrawTask, "draw trans field obj preChar", 2095, FldSceneDraw_UpdateDrwTrnsFldObjPCTask, NULL, NULL);
    KwlnTask_Create(fldSceneDrawTask, "draw persona model", 4168, FldSceneDraw_UpdateDrwPrsnaMdlTask, NULL, NULL);
    KwlnTask_Create(fldSceneDrawTask, "draw trans field object", 4172, FldSceneDraw_UpdateDrwTrnsFldObjTask, NULL, NULL);
    KwlnTask_Create(fldSceneDrawTask, "draw trans field", 4173, FldSceneDraw_UpdateDrwTrnsFldTask, NULL, NULL);
    KwlnTask_Create(fldSceneDrawTask, "draw trans field(sort)", 4183, FldSceneDraw_UpdateDrwTrnsFldSrtTask, NULL, NULL);
    KwlnTask_Create(fldSceneDrawTask, "draw trans NPC(sort)", 4183, FldSceneDraw_UpdateDrwTrnsNpcSrtTask, NULL, NULL);

    return fldSceneDrawTask;
}