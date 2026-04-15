#include "Kosaka/k_draw.h"
#include "kwln/kwlnTask.h"
#include "kwln/kwln.h"
#include "Primitive/primitive.h"

static RwRGBA sCylinderColor = {0, 168, 168, 168}; // 007cc1b8

// FUN_001a4660
void* K_Draw_UpdatePointTask(KwlnTask* pointTask)
{
    PointDrawWork* work;    

    work = (PointDrawWork*)pointTask->workData;

    if (!work->drawEnabled)
    {
        return KWLNTASK_CONTINUE;
    }

    primSphereLine3D(&work->center, 10.0f, &work->color, 1);

    return KWLNTASK_CONTINUE;
}

void K_Draw_DestroyPointTask(KwlnTask* pointTask)
{
    RW_FREE(pointTask->workData);
}

// FUN_001a46f0. Tiny sphere
KwlnTask* K_Draw_CreatePointTask(KwlnTask* parent)
{
    PointDrawWork* work;

    work = RW_CALLOC(1, sizeof(PointDrawWork), 0x40000);
    if (work == NULL)
    {
        return NULL;
    }

    return kwlnTaskCreateWithAutoPriority(parent,
                                          2109,
                                          "draw point",
                                          K_Draw_UpdatePointTask,
                                          K_Draw_DestroyPointTask,
                                          work);
}

// FUN_001a4770
void K_Draw_SetPointDrawEnabled(KwlnTask* pointTask, u32 drawEnabled)
{
    ((PointDrawWork*)pointTask->workData)->drawEnabled = drawEnabled;
}

// FUN_001a4780
void K_Draw_SetPointCenter(KwlnTask* pointTask, const RwV3d* center)
{
    ((PointDrawWork*)pointTask->workData)->center = *center;
}

// FUN_001a47e0
void K_Draw_SetPointColor(KwlnTask* pointTask, const RwRGBA* color)
{
    ((PointDrawWork*)pointTask->workData)->color = *color;
}

// FUN_001a47e0
void* K_Draw_UpdateCylinderTask(KwlnTask* cylinderTask)
{
    CylinderDrawWork* work;

    work = (CylinderDrawWork*)cylinderTask->workData;

    if (work->drawEnabled)
    {
        primCylinderLine3D(&work->center, work->radius, work->height, &sCylinderColor, 1);
    }

    return KWLNTASK_CONTINUE;
}

// FUN_001a4830
void K_Draw_DestroyCylinderTask(KwlnTask* cylinderTask)
{
    RW_FREE(cylinderTask->workData);
}

// FUN_001a4860
KwlnTask* K_Draw_CreateCylinderTask(KwlnTask* parent)
{
    CylinderDrawWork* work;

    work = RW_CALLOC(1, sizeof(CylinderDrawWork), 0x40000);
    if (work == NULL)
    {
        return NULL;
    }

    return kwlnTaskCreateWithAutoPriority(parent,
                                          2109,
                                          "field camera cylinder",  // this name is horrible btw
                                          K_Draw_UpdateCylinderTask,
                                          K_Draw_DestroyCylinderTask,
                                          work);
}

// FUN_001a48e0
void K_Draw_SetCylinderDrawEnabled(KwlnTask* cylinderTask, u32 drawEnabled)
{
    ((CylinderDrawWork*)cylinderTask->workData)->drawEnabled = drawEnabled;
}

// FUN_001a48f0
void K_Draw_SetCylinderCenter(KwlnTask* cylinderTask, const RwV3d* center)
{
    ((CylinderDrawWork*)cylinderTask->workData)->center = *center;
}

// FUN_001a4920
void K_Draw_SetCylinderRadius(KwlnTask* cylinderTask, f32 radius)
{
    ((CylinderDrawWork*)cylinderTask->workData)->radius = radius;
}

// FUN_001a4930
void K_Draw_SetCylinderHeight(KwlnTask* cylinderTask, f32 height)
{
    ((CylinderDrawWork*)cylinderTask->workData)->height = height;
}

// FUN_001a4c10
void* K_Draw_UpdatePositionTask(KwlnTask* positionTask)
{
    PositionDrawWork* work;

    work = (PositionDrawWork*)positionTask->workData;

    if (kwlnCameraBeginUpdate() != NULL)
    {
        primAxisLine3D(&work->mat, 60.0f, 1);
        primSphereLine3D(&work->mat.pos, 20.0f, &work->color, 1);

        kwlnCameraEndUpdate();
    }

    return KWLNTASK_CONTINUE;
}

// FUN_001a4ca0
void K_Draw_DestroyPositionTask(KwlnTask* positionTask)
{
    RW_FREE(positionTask->workData);
}

// FUN_001a4cd0
KwlnTask* K_Draw_CreatePositionTask(KwlnTask* parent)
{
    PositionDrawWork* work;
    KwlnTask* positionTask;

    work = RW_CALLOC(1, sizeof(PositionDrawWork), 0x40000);
    if (work == NULL)
    {
        return NULL;
    }

    positionTask = kwlnTaskCreate(parent,
                                  "position draw",
                                  4174,
                                  K_Draw_UpdatePositionTask,
                                  K_Draw_DestroyPositionTask,
                                  work);

    RwMatrixSetIdentity(&work->mat);
    work->color.r = 255;
    work->color.g = 0;
    work->color.b = 0;
    work->color.a = 255;

    return positionTask;
}

// FUN_001a4dc0
void K_Draw_SetPositionColor(KwlnTask* positionTask, const RwRGBA* color)
{
    ((PositionDrawWork*)positionTask->workData)->color = *color;
}

// FUN_001a4df0
void K_Draw_CopyPositionCenter(RwV3d* dst, KwlnTask* positionTask)
{
    PositionDrawWork* work = (PositionDrawWork*)positionTask->workData;
    RwV3d unsused = {0};

    *dst = work->mat.pos;
}

// FUN_001a4e50
RwMatrix* K_Draw_GetPositionMatrix(KwlnTask* positionTask)
{
    return &((PositionDrawWork*)positionTask->workData)->mat;
}

// FUN_001a4e60. Dumb name ngl
void K_Draw_SetPositionPos(KwlnTask* positionTask, const RwV3d* pos)
{
    PositionDrawWork* work;
    RwMatrixTolerance matTolerance;

    work = (PositionDrawWork*)positionTask->workData;

    work->mat.pos = *pos;

    RwEngineGetMatrixTolerances(&matTolerance);
    RwMatrixOptimize(&work->mat, &matTolerance);
    RwMatrixUpdate(&work->mat);
}

// FUN_001a4ed0
void K_Draw_MovePositionInDir(f32 dist, KwlnTask* positionTask, const RwV3d* dir)
{
    PositionDrawWork* work;
    RwV3d translation;

    work = (PositionDrawWork*)positionTask->workData;

    translation.x = dir->x * dist;
    translation.y = dir->y * dist;
    translation.z = dir->z * dist;

    RwMatrixTranslate(&work->mat, &translation, rwCOMBINEPOSTCONCAT);
}

// FUN_001a4f40
void K_Draw_RotatePosition(f32 angle, KwlnTask* positionTask, const RwV3d* axis)
{
    PositionDrawWork* work;
    RwV3d originalPos;
    RwV3d negPos;

    work = (PositionDrawWork*)positionTask->workData;
    originalPos = work->mat.pos;

    negPos.x = originalPos.x * -1.0f;
    negPos.y = originalPos.y * -1.0f;
    negPos.z = originalPos.z * -1.0f;

    RwMatrixTranslate(&work->mat, &negPos, rwCOMBINEPOSTCONCAT);
    RwMatrixRotate(&work->mat, axis, angle, rwCOMBINEPOSTCONCAT);
    RwMatrixTranslate(&work->mat, &originalPos, rwCOMBINEPOSTCONCAT);
}