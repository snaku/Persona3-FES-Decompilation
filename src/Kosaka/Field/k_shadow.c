#include "Kosaka/Field/k_shadow.h"
#include "Kernel/Kwln/kwlnTask.h"
#include "rw/rwcore.h"

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

// FUN_001997e0
//
// to help visualizing:
//
// (xLeft, yTop)  [0] --------- [2] (xRigth, yTop)
//                |   \           |
//                |     \         |
//                |       \       |
//                |         \     |
//                |           \   |
// (xLeft, yBot)  [1] --------- [3]  (xRight, yBot)
u32 K_FldShadow_Draw(f32 xLeft, f32 yTop,
                     f32 xRight, f32 yBot,
                     f32 zBufferNear, f32 recipZ,
                     const RwRGBA* topColor, const RwRGBA* botColor)
{
    RwIm2DVertex vertices[4];

    vertices[0].u.els.color.r = topColor->r;
    vertices[0].u.els.color.g = topColor->g;
    vertices[0].u.els.color.b = topColor->b;
    vertices[0].u.els.color.a = topColor->a;

    vertices[1].u.els.color.r = botColor->r;
    vertices[1].u.els.color.g = botColor->g;
    vertices[1].u.els.color.b = botColor->b;
    vertices[1].u.els.color.a = botColor->a;

    vertices[2].u.els.color.r = topColor->r;
    vertices[2].u.els.color.g = topColor->g;
    vertices[2].u.els.color.b = topColor->b;
    vertices[2].u.els.color.a = topColor->a;

    vertices[3].u.els.color.r = botColor->r;
    vertices[3].u.els.color.g = botColor->g;
    vertices[3].u.els.color.b = botColor->b;
    vertices[3].u.els.color.a = botColor->a;

    vertices[0].u.els.scrVertex.x = xLeft;
    vertices[0].u.els.scrVertex.y = yTop;
    vertices[0].u.els.scrVertex.z = zBufferNear;
    vertices[0].u.els.recipZ = recipZ;

    vertices[1].u.els.scrVertex.x = xLeft;
    vertices[1].u.els.scrVertex.y = yBot;
    vertices[1].u.els.scrVertex.z = zBufferNear;
    vertices[1].u.els.recipZ = recipZ;

    vertices[2].u.els.scrVertex.x = xRight;
    vertices[2].u.els.scrVertex.y = yTop;
    vertices[2].u.els.scrVertex.z = zBufferNear;
    vertices[2].u.els.recipZ = recipZ;

    vertices[3].u.els.scrVertex.x = xRight;
    vertices[3].u.els.scrVertex.y = yBot;
    vertices[3].u.els.scrVertex.z = zBufferNear;
    vertices[3].u.els.recipZ = recipZ;

    RwIm2DRenderPrimitive(rwPRIMTYPETRISTRIP, vertices, 4);

    return true;
}

// FUN_0019beb0
KwlnTask* K_FldShadow_CreateRenderTexTask(KwlnTask* parent, u16 resTypeId, s32 param_3)
{
    // TODO

    return NULL;
}

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