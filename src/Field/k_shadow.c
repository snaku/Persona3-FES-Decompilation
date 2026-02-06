#include "kwln/kwlnTask.h"
#include "Field/k_shadow.h"
#include "rw/rwplcore.h"

typedef struct
{
    RwRGBA col1;
    RwRGBA col2;
    RwRGBA col3;
    RwRGBA col4;
} ShadowColors;

// 00678960
static ShadowColors gShadowColors =
{
    {0, 0, 0, 0},
    {0, 0, 0, 0},
    {0, 0, 0, 255},
    {0, 0, 0, 255}
};

// FUN_0019c4b0
void* FldShadow_UpdateShadowMapTask(KwlnTask* fldShadowMapTask)
{
    // TODO

    return KWLN_TASK_CONTINUE;
}

// FUN_0019d270
void FldShadow_DestroyShadowMapTask(KwlnTask* fldShadowMapTask)
{
    RW_FREE(fldShadowMapTask->taskData);
}

// FUN_0019d2a0
KwlnTask* FldShadow_CreateShadowMapTask(KwlnTask* fldSceneDrawTask)
{
    FieldShadowMap* fldShadowMap;

    fldShadowMap = RW_CALLOC(1, sizeof(FieldShadowMap), 0x40000);
    if (fldShadowMap == NULL)
    {
        return NULL;
    }

    return KwlnTask_Create(fldSceneDrawTask, "shadow map camera", 2068, FldShadow_UpdateShadowMapTask, FldShadow_DestroyShadowMapTask, fldShadowMap);
}