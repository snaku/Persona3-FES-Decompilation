#include "Kosaka/Field/k_event.h"
#include "Kosaka/Field/k_unit.h"
#include "Model/mdlManager.h"
#include "kwln/kwlnTask.h"

KwlnTask* K_FldEvent_CreateDrawCmdTask(KwlnTask* fldEventTask);

// FUN_001c7130
u32 K_FldEvent_IsUnitWithinDistOfHero(const FldUnit* fldUnit, f32 maxDist)
{
    return K_FldEvent_AreUnitsWithinDist(fldUnit, &gFldUnits[FLDUNIT_HERO], maxDist);
}

// FUN_001c7160
u32 K_FldEvent_AreUnitsWithinDist(const FldUnit* fldUnitA, const FldUnit* fldUnitB, f32 maxDist)
{
    u32 withinDist;

    withinDist = false;
    if (fldUnitA->unk_48 != NULL && fldUnitB->unk_48 != NULL)
    {
        withinDist = K_FldEvent_ArePosWithinDist(&mdlGetMatrix(fldUnitA->mdl)->pos,
                                                 &mdlGetMatrix(fldUnitB->mdl)->pos,
                                                 maxDist);
    }

    return withinDist;
}

// FUN_001c71f0
u32 K_FldEvent_ArePosWithinDist(const RwV3d* posA, const RwV3d* posB, f32 maxDist)
{
    RwV3d diff;
    u32 withinDist;

    withinDist = false;

    diff.x = posA->x - posB->x;
    diff.y = posA->y - posB->y;
    diff.z = posA->z - posB->z;

    if (RwV3dLength(&diff) < maxDist)
    {
        withinDist = true;
    }

    return withinDist;
}

// FUN_001c8620
void* K_FldEvent_UpdateFldEventTask(KwlnTask* fldEventTask)
{
    // TODO

    return KWLNTASK_CONTINUE;
}

// FUN_001cd570
void K_FldEvent_DestroyFldEventTask(KwlnTask* fldEventTask)
{
    RW_FREE(fldEventTask->workData);
}

// FUN_001cd5a0. Create 'field event' and 'draw command' tasks
KwlnTask* K_FldEvent_CreateTasks(KwlnTask* fldRootTask)
{
    FldEvent* fldEvent;
    KwlnTask* fldEventTask;

    fldEvent = (FldEvent*)RW_CALLOC(1, sizeof(FldEvent), 0x40000);
    if (fldEvent == NULL)
    {
        return NULL;
    }

    fldEventTask = kwlnTaskCreateWithAutoPriority(fldRootTask, 10, "field event", K_FldEvent_UpdateFldEventTask, K_FldEvent_DestroyFldEventTask, fldEvent);
    
    fldEvent->drawCmdTask = K_FldEvent_CreateDrawCmdTask(fldEventTask);

    return fldEventTask;
}

// FUN_001cd690
void* K_FldEvent_UpdateDrawCmdTask(KwlnTask* drawCmdTask)
{
    // TODO

    return KWLNTASK_CONTINUE;
}

// FUN_001cd6e0
void K_FldEvent_DestroyDrawCmdTask(KwlnTask* drawCmdTask)
{
    RW_FREE(drawCmdTask->workData);
}

// FUN_001cd710
KwlnTask* K_FldEvent_CreateDrawCmdTask(KwlnTask* fldEventTask)
{
    FldDrawCmd* drawCmd;

    drawCmd = (FldDrawCmd*)RW_CALLOC(1, sizeof(FldDrawCmd), 0x40000);
    if (drawCmd == NULL)
    {
        return NULL;
    }

    return kwlnTaskCreateWithAutoPriority(fldEventTask, 4207, "draw command", K_FldEvent_UpdateDrawCmdTask, K_FldEvent_DestroyDrawCmdTask, drawCmd);
}