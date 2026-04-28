#include "Kosaka/Field/k_event.h"
#include "Kosaka/Field/k_unit.h"
#include "Kosaka/Field/k_majorIds.h"
#include "Scene/mt_scene.h"
#include "Scene/resrcManager.h"
#include "Model/mdlManager.h"
#include "kwln/kwlnTask.h"

KwlnTask* K_FldEvent_CreateDrawCmdTask(KwlnTask* fldEventTask);

// FUN_001c6200
u32 K_FldEvent_IsPosWithinFov(const RwMatrix* viewerMat, const RwV3d* targetPos, f32 fov)
{
    // TODO
}

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

// FUN_001c74c0
ResrcModelNpc* K_FldEvent_FindInteractableNpc()
{
    ResrcModelNpc* npc;
    ResrcModelNpc* interactableNpc;
    RwV3d lookAtPos;
    RwV3d distDiff;
    u32 isWithinFov;
    s32 currAnimId;

    npc = (ResrcModelNpc*)MT_Scene_GetResListHead(RESRC_TYPE_MODELNPC);
    interactableNpc = NULL;
    while (npc != NULL)
    {
        isWithinFov = K_FldEvent_IsPosWithinFov(mdlGetMatrix(gFldUnits[FLDUNIT_HERO].mdl),
                                                &mdlGetMatrix(npc->mdl)->pos,
                                                120.0f);
        if (isWithinFov == true)
        {
            distDiff.x = mdlGetMatrix(npc->mdl)->pos.x - mdlGetMatrix(gFldUnits[FLDUNIT_HERO].mdl)->pos.x;
            distDiff.y = mdlGetMatrix(npc->mdl)->pos.y - mdlGetMatrix(gFldUnits[FLDUNIT_HERO].mdl)->pos.y;
            distDiff.z = mdlGetMatrix(npc->mdl)->pos.z - mdlGetMatrix(gFldUnits[FLDUNIT_HERO].mdl)->pos.z;

            if (RwV3dLength(&distDiff) < 200.0f)
            {
                lookAtPos = mdlGetMatrix(gFldUnits[FLDUNIT_HERO].mdl)->pos;
                lookAtPos.y += 140.0f;

                mdlLookAtSetTargetPosXYZ(npc->mdl, &lookAtPos);
                mdlLookAtSetFlags(npc->mdl, mdlLookAtGetFlags(npc->mdl) | MDLLOOKAT_FLAG_UNK1000);

                if (interactableNpc == NULL)
                {
                    interactableNpc = npc;
                }

                if (gMtScene->fldMajorId == FIELD_MAJOR_ID_DORM)
                {
                    currAnimId = mdlAnimGetId(npc->mdl, 0);
                    if (currAnimId >= 4)
                    {
                        if (currAnimId % 2 == 0)
                        {
                            mdlAnimSet(npc->mdl, 0, currAnimId + 1, 7, MDLANIM_FLAG_UNK01);
                        }
                    }
                }
            }
            else
            {
                mdlLookAtDisableTarget(npc->mdl);

                if (gMtScene->fldMajorId == FIELD_MAJOR_ID_DORM)
                {
                    currAnimId = mdlAnimGetId(npc->mdl, 0);
                    if (currAnimId >= 4)
                    {
                        if (currAnimId % 2 == 1)
                        {
                            mdlAnimSet(npc->mdl, 0, currAnimId - 1, 7, MDLANIM_FLAG_UNK01);
                        }
                    }
                }
            }
        }
        else
        {
            mdlLookAtDisableTarget(npc->mdl);

            if (gMtScene->fldMajorId == FIELD_MAJOR_ID_DORM)
            {
                currAnimId = mdlAnimGetId(npc->mdl, 0);
                if (currAnimId >= 4)
                {
                    if (currAnimId % 2 == 1)
                    {
                        mdlAnimSet(npc->mdl, 0, currAnimId - 1, 7, MDLANIM_FLAG_UNK01);
                    }
                }
            }
        }

        npc = (ResrcModelNpc*)npc->base.next;
    }

    return interactableNpc;
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
    RwFree(fldEventTask->workData);
}

// FUN_001cd5a0. Create 'field event' and 'draw command' tasks
KwlnTask* K_FldEvent_CreateTasks(KwlnTask* fldRootTask)
{
    FldEvent* fldEvent;
    KwlnTask* fldEventTask;

    fldEvent = (FldEvent*)RwCalloc(1, sizeof(FldEvent), rwMEMHINTDUR_GLOBAL);
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
    RwFree(drawCmdTask->workData);
}

// FUN_001cd710
KwlnTask* K_FldEvent_CreateDrawCmdTask(KwlnTask* fldEventTask)
{
    FldDrawCmd* drawCmd;

    drawCmd = (FldDrawCmd*)RwCalloc(1, sizeof(FldDrawCmd), rwMEMHINTDUR_GLOBAL);
    if (drawCmd == NULL)
    {
        return NULL;
    }

    return kwlnTaskCreateWithAutoPriority(fldEventTask, 4207, "draw command", K_FldEvent_UpdateDrawCmdTask, K_FldEvent_DestroyDrawCmdTask, drawCmd);
}