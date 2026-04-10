#include "Kosaka/k_draw.h"
#include "kwln/kwlnTask.h"

// FUN_001a47e0
void* K_Draw_UpdateCylinderTask(KwlnTask* cylinderTask)
{
    // TODO

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