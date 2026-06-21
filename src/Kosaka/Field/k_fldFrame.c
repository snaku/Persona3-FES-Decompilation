#include "Kosaka/Field/k_fldFrame.h"
#include "Kosaka/Field/k_unit.h"
#include "Kosaka/Field/k_sceneDraw.h"
#include "Kosaka/k_footstep.h"
#include "Model/mdlManager.h"
#include "kwln/kwlnTask.h"
#include "kwln/kwln.h"
#include "Primitive/primitive.h"
#include "Scene/mt_scene.h"
#include "Scene/resrcManager.h"
#include "temporary.h"

#define COLLISCTL_SUBSTEPS 3

static RwRGBA sDebugSphereColor = {0, 168, 168, 168};

KwlnTask* K_FldFrame_CreateCollisSphereTask(KwlnTask* parent);
void K_FldFrame_CollisSphereSetDrawEnabled(KwlnTask* collisSphereTask, u32 drawEnabled);

// FUN_001aaad0
u32 K_FldFrame_IsPointInTriangle(const RwV3d* point, const RwV3d** tri, const RwV3d* normal)
{
    // TODO

    return false;
}

// FUN_001ac750
void K_FldFrame_HandleCollis(const RwV3d* pos, RwV3d* translation, f32 sphereCollisRadius, u16 resTypeId)
{
    // TODO
}

// FUN_001acc30
u32 K_FldFrame_Raycast(const RwV3d* line, RwV3d* hitPointDst)
{
    // TODO

    return false;
}

// FUN_001ad2f0
void* K_FldFrame_UpdateCtlTask(KwlnTask* collisCtlTask)
{
    CollisCtl* ctl;
    ResrcModelChar* charList; // unused
    ResrcModelNpc* npcList;   // unused
    RwMatrix* mdlMatrix;
    RwV3d line[2];
    RwV3d hitPoint;
    RwV3d translation;
    RwV3d pos;
    s32 i;

    ctl = (CollisCtl*)collisCtlTask->workData;

    charList = (ResrcModelChar*)MT_Scene_GetResListHead(RESRC_TYPE_MODELCHAR);
    npcList = (ResrcModelNpc*)MT_Scene_GetResListHead(RESRC_TYPE_MODELNPC);

    if (ctl->flags & COLLISCTL_FLAG_NOUPDATE)
    {
        return KWLNTASK_CONTINUE;
    }

    switch (ctl->state)
    {
        case COLLISCTL_STATE_DIRTY:
            mdlMatrix = mdlGetMatrix(ctl->mdl);
            pos = mdlMatrix->pos;

            if (ctl->flags & COLLISCTL_FLAG_GROUNDSNAP && 
                !(ctl->flags & COLLISCTL_FLAG_NOCOLLIS))
            {
                line[0] = line[1] = pos;

                if (K_Scene_001a0250())
                {
                    line[0].y += 600.0f;
                }
                else
                {
                    line[0].y += 200.0f;
                }

                line[1].y -= 1000.0f;

                if (K_FldFrame_Raycast(line, &hitPoint) == true)
                {
                    ctl->velocity.y = -(pos.y - hitPoint.y);
                }
            }

            for (i = 0; i < COLLISCTL_SUBSTEPS; i++)
            {
                translation.x = ctl->velocity.x / COLLISCTL_SUBSTEPS;
                translation.y = ctl->velocity.y / COLLISCTL_SUBSTEPS;
                translation.z = ctl->velocity.z / COLLISCTL_SUBSTEPS;

                pos = mdlGetMatrix(ctl->mdl)->pos;
                pos.y += ctl->sphereCollisRadius;

                if (!(ctl->flags & COLLISCTL_FLAG_NOCOLLIS))
                {
                    K_FldFrame_HandleCollis(&pos, &translation, ctl->sphereCollisRadius, ctl->resTypeId);
                }

                mdlTranslate(ctl->mdl, &translation, rwCOMBINEPOSTCONCAT);
            }

            ctl->xGrid = (mdlMatrix->pos.x + 400.0f) / 800.0f;
            ctl->zGrid = (mdlMatrix->pos.z + 400.0f) / 800.0f;

            if (RESRC_GET_ID(ctl->resTypeId) < 100)
            {
                K_Footstep_Update(ctl->mdl, ctl->charId, ctl->resTypeId);
            }

            ctl->state++; // COLLISCTL_STATE_NOTDIRTY
            break;

        case COLLISCTL_STATE_NOTDIRTY:
            mdlMatrix = mdlGetMatrix(ctl->mdl);

            if (ctl->flags & COLLISCTL_FLAG_DEBUGDRAW)
            {
                K_FldFrame_CollisSphereSetDrawEnabled(collisCtlTask->child, true);
            }
            else
            {
                K_FldFrame_CollisSphereSetDrawEnabled(collisCtlTask->child, false);
            }
            break;
        
        case COLLISCTL_STATE_IDLE: break;
    }

    return KWLNTASK_CONTINUE;
}

// FUN_001ad630
void K_FldFrame_DestroyCtlTask(KwlnTask* collisCtlTask)
{
    RwFree(collisCtlTask->workData);
}

// FUN_001ad660
KwlnTask* K_FldFrame_CreateCtlTask(KwlnTask* parent, u32 resTypeId, s32 unused, f32 sphereCollisRadius)
{
    KwlnTask* task;
    CollisCtl* ctl;
    Resrc* res;
    FldUnit* units;
    s32 i;
    u16 _resTypeId;

    ctl = RwCalloc(1, sizeof(CollisCtl), rwMEMHINTDUR_GLOBAL);
    if (ctl == NULL)
    {
        return NULL;
    }

    task = kwlnTaskCreateWithAutoPriority(parent,
                                          10,
                                          "collision controler",
                                          K_FldFrame_UpdateCtlTask,
                                          K_FldFrame_DestroyCtlTask,
                                          ctl);

    ctl->state = COLLISCTL_STATE_NOTDIRTY;
    _resTypeId = resTypeId; // to force andi a0, s2, 0xffff here
    ctl->resTypeId = _resTypeId;
    ctl->sphereCollisRadius = sphereCollisRadius;
    ctl->unk_24 = 0;

    if (RESRC_GET_TYPE(_resTypeId) == RESRC_TYPE_MODELCHAR)
    {
        res = MT_Scene_GetRes(_resTypeId);
        if (res != NULL)
        {
            ctl->mdl = ((ResrcModelChar*)res)->mdl;
        }

        i = 0;
        units = gFldUnitsPc; // regswap (should be a2 instead of a3)
        for (; i < FLDUNIT_PC_MAX; i++)
        {
            if (units[i].genusBase != NULL &&
                units[i].mdl == ((ResrcModelChar*)res)->mdl)
            {
                ctl->charId = gFldUnitsPc[i].charId;
                ctl->fldUnit = &units[i];
                break;
            }
        }

        i = 0;
        units = gFldUnitsEc; // regswap (should be a2 instead of a3)
        for (; i < FLDUNIT_EC_MAX; i++)
        {
            if (units[i].genusBase != NULL &&
                units[i].mdl == ((ResrcModelChar*)res)->mdl)
            {
                ctl->charId = gFldUnitsEc[i].charId;
                ctl->fldUnit = &units[i];
                break;
            }
        }
    }
    else if (RESRC_GET_TYPE(_resTypeId) == RESRC_TYPE_MODELNPC)
    {
        res = MT_Scene_GetRes(_resTypeId);
        if (res != NULL)
        {
            ctl->mdl = ((ResrcModelNpc*)res)->mdl;
        }
    }

    K_FldFrame_CreateCollisSphereTask(task);

    return task;
}

// FUN_001ad8b0
f32 K_FldFrame_CtlGetSphereCollisRadius(KwlnTask* collisCtlTask)
{
    return ((CollisCtl*)collisCtlTask->workData)->sphereCollisRadius;
}

// FUN_001ad8c0
void K_FldFrame_CtlSetSphereCollisRadius(KwlnTask* collisCtlTask, f32 radius)
{
    CollisCtl* ctl;

    ctl = (CollisCtl*)collisCtlTask->workData;
    ctl->sphereCollisRadius = radius;

    if (radius == 0.0f)
    {
        ctl->flags |= COLLISCTL_FLAG_NOCOLLIS;
        return;
    }

    ctl->flags &= ~COLLISCTL_FLAG_NOCOLLIS;
}

// FUN_001ad910
s32 K_FldFrame_CtlGetXGrid(KwlnTask* collisCtlTask)
{
    return ((CollisCtl*)collisCtlTask->workData)->xGrid;
}

// FUN_001ad920
s32 K_FldFrame_CtlGetZGrid(KwlnTask* collisCtlTask)
{
    return ((CollisCtl*)collisCtlTask->workData)->zGrid;
}

// FUN_001ad940
void K_FldFrame_CtlCopyPos(RwV3d* dst, KwlnTask* collisCtlTask)
{
    CollisCtl* ctl = (CollisCtl*)collisCtlTask->workData;
    RwV3d vec = {0};

    if (ctl->mdl != NULL)
    {
        vec = mdlGetMatrix(ctl->mdl)->pos;
    }

    *dst = vec;
}

// FUN_001ad9e0
void K_FldFrame_CtlUpdateMdlMat(KwlnTask* collisCtlTask, const RwMatrix* mat)
{
    // TODO
}

// FUN_001addf0
void K_FldFrame_CtlMoveInDir(f32 dist, KwlnTask* collisCtlTask, const RwV3d* normalizedDir)
{
    CollisCtl* ctl;
    RwV3d velocity;

    ctl = (CollisCtl*)collisCtlTask->workData;
    velocity = *normalizedDir;

    if (ctl->state == COLLISCTL_STATE_NOTDIRTY)
    {
        velocity.x *= dist;
        velocity.y *= dist;
        velocity.z *= dist;
        
        ctl->totalDist += (u32)dist;
        ctl->velocity = velocity;

        ctl->state = COLLISCTL_STATE_DIRTY;
    }
}

// FUN_001adec0
void K_FldFrame_CtlMoveForward(f32 dist, KwlnTask* collisCtlTask)
{
    CollisCtl* ctl = (CollisCtl*)collisCtlTask->workData;
    RwV3d velocity = {0};

    if (ctl->state == COLLISCTL_STATE_NOTDIRTY)
    {
        velocity = mdlGetMatrix(ctl->mdl)->at;
        RwV3dNormalize(&velocity, &velocity);
        
        velocity.x *= dist;
        velocity.y *= dist;
        velocity.z *= dist;

        ctl->totalDist += (u32)dist;
        ctl->velocity = velocity;

        ctl->state = COLLISCTL_STATE_DIRTY;
    }
}

// FUN_001adff0
void K_FldFrame_CtlRotate(KwlnTask* collisCtlTask, const RwV3d* axis, f32 angle)
{
    CollisCtl* ctl;
    RwV3d originalPos;
    RwV3d negPos;

    ctl = (CollisCtl*)collisCtlTask->workData;

    if (ctl->mdl != NULL)
    {
        originalPos = mdlGetMatrix(ctl->mdl)->pos;

        negPos.x = originalPos.x * -1.0f;
        negPos.y = originalPos.y * -1.0f;
        negPos.z = originalPos.z * -1.0f;

        mdlTranslate(ctl->mdl, &negPos, rwCOMBINEPOSTCONCAT); // basically just do pos + (-pos) = (0, 0, 0)
        mdlRotate(ctl->mdl, axis, angle, rwCOMBINEPOSTCONCAT);
        mdlTranslate(ctl->mdl, &originalPos, rwCOMBINEPOSTCONCAT);
    }
}

// FUN_001ae290
void* K_FldFrame_UpdateCollisSphereTask(KwlnTask* collisSphereTask)
{
    // TODO

    return KWLNTASK_CONTINUE;
}

// FUN_001ae3c0
void K_FldFrame_DestroyCollisSphereTask(KwlnTask* collisSphereTask)
{
    RwFree(collisSphereTask->workData);
}

// FUN_001ae3f0
KwlnTask* K_FldFrame_CreateCollisSphereTask(KwlnTask* parent)
{
    CollisSphereDebug* work;

    work = RwCalloc(1, sizeof(CollisSphereDebug), rwMEMHINTDUR_GLOBAL);
    if (work == NULL)
    {
        return NULL;
    }

    return kwlnTaskCreate(parent,
                          "collis sphere",
                          4174,
                          K_FldFrame_UpdateCollisSphereTask,
                          K_FldFrame_DestroyCollisSphereTask,
                          work);
}

// FUN_001ae470
void K_FldFrame_CollisSphereSetDrawEnabled(KwlnTask* collisSphereTask, u32 drawEnabled)
{
    ((CollisSphereDebug*)collisSphereTask->workData)->drawEnabled = drawEnabled;
}