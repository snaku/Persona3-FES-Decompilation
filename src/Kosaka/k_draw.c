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