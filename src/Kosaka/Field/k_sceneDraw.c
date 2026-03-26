#include "Kosaka/Field/k_sceneDraw.h"
#include "Kosaka/Field/k_shadow.h"
#include "kwln/kwlnTask.h"

// FUN_0019d410. 'draw opac field'
void* K_FldSceneDraw_UpdateDrwOpcFldTask(KwlnTask* drwOpcFld)
{
    // TODO
    
    return KWLN_TASK_CONTINUE;
}

// FUN_0019d4a0. 'draw trans field'
void* K_FldSceneDraw_UpdateDrwTrnsFldTask(KwlnTask* drwTrnsFldTask)
{
    // TODO

    return KWLN_TASK_CONTINUE;
}

// FUN_0019d530. 'draw trans field(sort)'
void* K_FldSceneDraw_UpdateDrwTrnsFldSrtTask(KwlnTask* drwTrnsFldSrtTask)
{
    // TODO

    return KWLN_TASK_CONTINUE;
}

// FUN_0019d780. 'draw opac field object'
void* K_FldSceneDraw_UpdateDrwOpcFldObjTask(KwlnTask* drwOpcFldTask)
{
    // TODO
    
    return KWLN_TASK_CONTINUE;
}

// FUN_0019de40. 'draw trans field object'
void* K_FldSceneDraw_UpdateDrwTrnsFldObjTask(KwlnTask* drwTrnsFldObjTask)
{
    // TODO

    return KWLN_TASK_CONTINUE;
}

// FUN_0019e1b0. 'draw trans field obj preChar'
void* K_FldSceneDraw_UpdateDrwTrnsFldObjPCTask(KwlnTask* drwTrnsFldObjPCTask)
{
    // TODO

    return KWLN_TASK_CONTINUE;
}

// FUN_0019e330. 'draw character model'
void* K_FldSceneDraw_UpdateDrwChrMdlTask(KwlnTask* drwChrMdlTask)
{
    // TODO

    return KWLN_TASK_CONTINUE;
}

// FUN_0019ef80. 'draw trans NPC(sort)'
void* K_FldSceneDraw_UpdateDrwTrnsNpcSrtTask(KwlnTask* drwTrnsNpcSrtTask)
{
    // TODO

    return KWLN_TASK_CONTINUE;
}

// FUN_0019f470. 'draw persona model'
void* K_FldSceneDraw_UpdateDrwPrsnaMdlTask(KwlnTask* drwPrsnaMdlTask)
{
    // TODO

    return KWLN_TASK_CONTINUE;
}

// FUN_0019f730
KwlnTask* K_FldSceneDraw_CreateTasks(KwlnTask* rootProcTask)
{
    KwlnTask* fldSceneDrawTask;

    fldSceneDrawTask = KwlnTask_CreateWithAutoPriority(rootProcTask, 10, "scene draw CTL", NULL, NULL, NULL);

    FldShadow_CreateShadowMapTask(fldSceneDrawTask);
    KwlnTask_Create(fldSceneDrawTask, "draw opac field", 2070, K_FldSceneDraw_UpdateDrwOpcFldTask, NULL, NULL);
    KwlnTask_Create(fldSceneDrawTask, "draw opac field object", 2071, K_FldSceneDraw_UpdateDrwOpcFldObjTask, NULL, NULL);
    KwlnTask_Create(fldSceneDrawTask, "draw character model", 2084, K_FldSceneDraw_UpdateDrwChrMdlTask, NULL, NULL);
    KwlnTask_Create(fldSceneDrawTask, "draw trans field obj preChar", 2095, K_FldSceneDraw_UpdateDrwTrnsFldObjPCTask, NULL, NULL);
    KwlnTask_Create(fldSceneDrawTask, "draw persona model", 4168, K_FldSceneDraw_UpdateDrwPrsnaMdlTask, NULL, NULL);
    KwlnTask_Create(fldSceneDrawTask, "draw trans field object", 4172, K_FldSceneDraw_UpdateDrwTrnsFldObjTask, NULL, NULL);
    KwlnTask_Create(fldSceneDrawTask, "draw trans field", 4173, K_FldSceneDraw_UpdateDrwTrnsFldTask, NULL, NULL);
    KwlnTask_Create(fldSceneDrawTask, "draw trans field(sort)", 4183, K_FldSceneDraw_UpdateDrwTrnsFldSrtTask, NULL, NULL);
    KwlnTask_Create(fldSceneDrawTask, "draw trans NPC(sort)", 4183, K_FldSceneDraw_UpdateDrwTrnsNpcSrtTask, NULL, NULL);

    return fldSceneDrawTask;
}