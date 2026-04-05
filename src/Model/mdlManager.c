#include "Model/mdlManager.h"
#include "Model/mdlFile.h"
#include "rw/rpworld.h"
#include "rw/rphanim.h"
#include "temporary.h"
#include "h_cdvd.h"

const f32 gFrameDuration = (1.0f / 30.0f);   // 007cadd4. 33.3ms. Not sure where to place this

static Model* sMdlListTails[MODEL_TYPE_MAX]; // 009571f0. Tails of each model type

u8 MdlStream_Read(Model* mdl);

void MdlStream_Init(Model* mdl);
void MdlStream_SetRmdFileMemory(Model* mdl, MdlRmdFileMemory* rmd);
void MdlStream_RequestCdvd(Model* mdl, const char* path);
void MdlStream_Destroy(Model* mdl);

// FUN_00311310
MdlAnimEntryTable* Mdl_CreateAnimEntryTable(u16 animCount)
{
    MdlAnimEntryTable* table;
    u32 size;
    u32 i;

    size = animCount * sizeof(MdlAnimEntry) + sizeof(MdlAnimEntryTable);
    table = (MdlAnimEntryTable*)RW_MALLOC(size, 0x40000);
    memset(table, 0, size);

    table->entries = (MdlAnimEntry*)((u8*)table + sizeof(MdlAnimEntryTable));
    table->count = animCount;

    for (i = 0; i < table->count; i++)
    {
        RwMatrixSetIdentity(&table->entries[i].identityMat);
    }

    table->unk_06 = 1;

    return table;
}

// FUN_00316690. TODO
Model* MdlManager_InitMdl(u16 type, u16 id)
{
    // TODO

    return NULL;
}

// FUN_00316910. Search a model in list by its type, id and flags. Set 'flags' to 0 if no flag filter
Model* MdlManager_Search(u16 type, u16 id, u16 flags)
{
    Model* mdl;

    mdl = sMdlListTails[type];
    while (mdl != NULL)
    {
        if (mdl->id == id)
        {
            if (flags != 0)
            {
                if (mdl->flags & flags)
                {
                    break;
                }
            }
            else
            {
                break;
            }
        }

        mdl = mdl->prev;
    }

    return mdl;
}

// FUN_00316b40
Model* MdlManager_CreateMdlFromPath(u16 type, u16 id, const char* path, u32 cdvdRead)
{
    Model* mdl;

    mdl = MdlManager_InitMdl(type, id);

    if (cdvdRead & MDL_CDVDREAD_SYNC)
    {
        mdl->flags |= MDL_FLAG_CDVDREADSYNC;
    }

    MdlStream_Init(mdl);
    MdlStream_RequestCdvd(mdl, path);

    MdlStream_Read(mdl);

    return mdl;
}

// FUN_00316bd0. Create a model with a loaded .RMD file in memory
Model* MdlManager_CreateMdlFromRmdMemory(u16 type, u16 id, void* rmdMemory, u32 rmdSize, u32 cdvdRead)
{
    Model* mdl;
    MdlRmdFileMemory rmd;

    mdl = MdlManager_InitMdl(type, id);

    if (cdvdRead & MDL_CDVDREAD_SYNC)
    {
        mdl->flags |= MDL_FLAG_CDVDREADSYNC;
    }

    MdlStream_Init(mdl);

    rmd.memory = rmdMemory;
    rmd.size = rmdSize;
    MdlStream_SetRmdFileMemory(mdl, &rmd);

    MdlStream_Read(mdl);

    return mdl;
}

// FUN_00316e00. Only for .RMD in 'MODEL' folder (See enum 'ModelType')
Model* MdlManager_CreateMdlAndResolvePath(u16 type, u16 id, u32 cdvdRead)
{
    // TODO

    return NULL;
}

// FUN_00316f70
u8 MdlStream_Read(Model* mdl)
{
    // TODO

    return true;
}

// FUN_00318870
f32 MdlAnim_GetDurationInFrame(Model* mdl, u16 slotIdx)
{
    f32 duration;

    if (mdl->animSlots[slotIdx].anim.id < 0)
    {
        duration = 0.0f;
    }
    else
    {
        if (mdl->animSlots[slotIdx].anim.hierarchy == NULL ||
           (mdl->animSlots[slotIdx].anim.hierarchy->currentAnim == NULL))
        {
            duration = 0.0f;
        }
        else
        {
            if (mdl->animSlots[slotIdx].anim.hierarchy->currentAnim->pCurrentAnim == NULL)
            {
                duration = 0.0f;
            }
            else
            {
                duration = mdl->animSlots[slotIdx].anim.hierarchy->currentAnim->pCurrentAnim->duration;
            }
        }
    }

    return duration / gFrameDuration;
}

// FUN_00318910
f32 MdlAnim_GetDurationInFrameById(Model* mdl, u16 slotIdx, s16 animId)
{
    f32 duration;

    if (mdl->animSlots[slotIdx].anim.hierarchy == NULL)
    {
        duration = 0.0f;
    }
    else
    {
        duration = mdl->animSlots[slotIdx].anim.table->entries[animId].rtAnim->duration;
    }

    return duration / gFrameDuration;
}

// FUN_00318990
f32 MdlAnim_GetCurrentFrame(Model* mdl, u16 slotIdx)
{
    f32 currTime;

    if (mdl->animSlots[slotIdx].anim.id < 0)
    {
        currTime = 0.0f;
    }
    else
    {
        currTime = mdl->animSlots[slotIdx].anim.currTime;
    }

    return currTime / gFrameDuration;
}

// FUN_00318a30
void Mdl_Translate(Model* mdl, const RwV3d* translation, RwOpCombineType combineOp)
{
    RwMatrixTranslate(&mdl->mat, translation, combineOp);
}

// FUN_00318a50
void Mdl_Rotate(Model* mdl, const RwV3d* axis, f32 angle, RwOpCombineType combineOp)
{
    RwMatrixRotate(&mdl->mat, axis, angle, combineOp);
}

// FUN_00318ad0
void Mdl_SetColor(Model* mdl, RwRGBA* color)
{
    mdl->color = *color;
}

// FUN_00318b00
RwRGBA* Mdl_GetColor(Model* mdl)
{
    return &mdl->color;
}

// FUN_00318b60
RwMatrix* Mdl_GetMatrix(Model* mdl)
{
    return &mdl->mat;
}

// FUN_00318b70
RwFrame* Mdl_GetClumpFrame(Model* mdl)
{
    return (RwFrame*)mdl->clump->object.parent;
}

// FUN_00318b80
RpClump* Mdl_GetClump(Model* mdl)
{
    return mdl->clump;
}

// FUN_00319010
void Mdl_EnableFullShadow(Model* mdl)
{
    mdl->flags |= MDL_FLAG_FULLSHADOW;
}

// FUN_00319030
void Mdl_DisableFullShadow(Model* mdl)
{
    mdl->flags &= ~MDL_FLAG_FULLSHADOW;
}

// FUN_00319090
void MdlLookAt_SetBlendRotFactor(Model* mdl, f32 blendRotFactor)
{
    mdl->animSlots[0].lookAt.blendRotFactor = blendRotFactor;
}

// FUN_003190a0
void MdlLookAt_SetMaxAngles(Model* mdl, f32 maxPitchAngle, f32 maxYawAngle)
{
    mdl->animSlots[0].lookAt.maxPitchAngle = maxPitchAngle;
    mdl->animSlots[0].lookAt.maxYawAngle = maxYawAngle;
}

// FUN_003190b0
void MdlLookAt_SetTargetPosXYZ(Model* mdl, RwV3d* target)
{
    mdl->animSlots[0].lookAt.flags |= MDL_LOOKAT_FLAG_XYZ;
    mdl->animSlots[0].lookAt.flags &= ~(MDL_LOOKAT_FLAG_XYZCS | MDL_LOOKAT_FLAG_XY);
    mdl->animSlots[0].lookAt.flags &= ~MDL_LOOKAT_FLAG_NOTARGET;

    mdl->animSlots[0].lookAt.targetPos = *target;
}

// FUN_00319100
void MdlLookAt_SetTargetPosXYZCS(Model* mdl, RwV3d* target)
{
    mdl->animSlots[0].lookAt.flags |= MDL_LOOKAT_FLAG_XYZCS;
    mdl->animSlots[0].lookAt.flags &= ~(MDL_LOOKAT_FLAG_XYZ | MDL_LOOKAT_FLAG_XY);
    mdl->animSlots[0].lookAt.flags &= ~MDL_LOOKAT_FLAG_NOTARGET;

    mdl->animSlots[0].lookAt.targetPos = *target;
}

// FUN_00319150
void MdlLookAt_SetTargetPosXY(Model* mdl, f32 xTarget, f32 yTarget)
{
    mdl->animSlots[0].lookAt.flags |= MDL_LOOKAT_FLAG_XY;
    mdl->animSlots[0].lookAt.flags &= ~(MDL_LOOKAT_FLAG_XYZCS | MDL_LOOKAT_FLAG_XYZ);
    mdl->animSlots[0].lookAt.flags &= ~MDL_LOOKAT_FLAG_NOTARGET;

    mdl->animSlots[0].lookAt.targetPos.x = xTarget;
    mdl->animSlots[0].lookAt.targetPos.y = yTarget;
}

// FUN_00319190
void MdlLookAt_DisableTarget(Model* mdl)
{
    mdl->animSlots[0].lookAt.flags |= MDL_LOOKAT_FLAG_NOTARGET;
}

// FUN_003191d0
u8 MdlLookAt_IsActive(Model* mdl)
{
    return (mdl->animSlots[0].lookAt.flags & (MDL_LOOKAT_FLAG_XYZCS |
                                              MDL_LOOKAT_FLAG_XYZ   |
                                              MDL_LOOKAT_FLAG_XY    | 
                                              MDL_LOOKAT_FLAG_NOTARGET)) != 0;
}

// FUN_00319210
void MdlLookAt_SetTargetScale(Model* mdl, RwV3d* scale)
{
    mdl->animSlots[0].lookAt.targetScale = *scale;
}

// FUN_00319840
void MdlStream_Init(Model* mdl)
{
    MdlStream* stream;

    stream = RW_MALLOC(sizeof(MdlStream), 0x40000);
    mdl->stream = stream;
    memset(stream, 0, sizeof(MdlStream));
}

// FUN_003198a0
void MdlStream_SetRmdFileMemory(Model* mdl, MdlRmdFileMemory* rmd)
{
    MdlStream* stream;
    stream = mdl->stream;

    stream->rmd.memory = rmd->memory;
    stream->rmd.size = rmd->size;
}

// FUN_003198c0
void MdlStream_RequestCdvd(Model* mdl, const char* path)
{
    MdlStream* stream;
    stream = mdl->stream;

    stream->cdvd = H_Cdvd_Request(path, H_CDVD_FILENORMAL);
    stream->rws = NULL;
}

// FUN_00319910
void MdlStream_Destroy(Model* mdl)
{
    if (mdl->stream->unk_0c != NULL)
    {
        RW_FREE(mdl->stream->unk_0c);
    }

    RW_FREE(mdl->stream);
    mdl->stream = NULL;
}