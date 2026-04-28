#include "Kosaka/Field/k_shadow.h"
#include "kwln/kwlnTask.h"
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
void* K_FldShadow_UpdateShadowMapTask(KwlnTask* fldShadowMapTask)
{
    // TODO

    return KWLNTASK_CONTINUE;
}

// FUN_0019d270
void K_FldShadow_DestroyShadowMapTask(KwlnTask* fldShadowMapTask)
{
    RwFree(fldShadowMapTask->workData);
}

// FUN_0019d2a0
KwlnTask* K_FldShadow_CreateShadowMapTask(KwlnTask* fldSceneDrawTask)
{
    FldShadowMap* fldShadowMap;

    fldShadowMap = (FldShadowMap*)RwCalloc(1, sizeof(FldShadowMap), rwMEMHINTDUR_GLOBAL);
    if (fldShadowMap == NULL)
    {
        return NULL;
    }

    return kwlnTaskCreate(fldSceneDrawTask, "shadow map camera", 2068, K_FldShadow_UpdateShadowMapTask, K_FldShadow_DestroyShadowMapTask, fldShadowMap);
}