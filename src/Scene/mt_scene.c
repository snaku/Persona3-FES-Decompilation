#include "Scene/mt_scene.h"
#include "Scene/resrcManager.h"
#include "Kosaka/Field/k_fldrc.h"
#include "Kosaka/Field/k_fldFrame.h"
#include "Kosaka/Field/k_sceneDraw.h"
#include "Kosaka/Field/k_shadow.h"
#include "Model/mdlManager.h"
#include "rw/rwplcore.h"
#include "temporary.h"

static MtScene sMtScene;       // 0095afc0
MtScene* gMtScene = &sMtScene; // 007cd540

// FUN_003b5760
void MT_Scene_Load(s32 fldMajorId, s32 fldMinorId)
{
    gMtScene->flags = 0;

    if (gMtScene->fldMajorId == fldMajorId && 
        gMtScene->fldMinorId == fldMinorId &&
       (fldMajorId < 20 || fldMajorId > 28))
    {
        printf("Scene data cashe hit!! major=%d minor=%d\n", fldMajorId, fldMinorId);
        gMtScene->flags |= MTSCENE_FLAG_CACHE;

        return;
    }

    MT_Scene_Destroy();

    K_Fldrc_RequestFldPac(fldMajorId, fldMinorId);
    K_Fldrc_001b0a20(fldMajorId, fldMinorId);

    gMtScene->fldFilterTask = K_Fldrc_CreateFilterTask(NULL);
    gMtScene->fldMajorId = fldMajorId;
    gMtScene->fldMinorId = fldMinorId;
    gMtScene->unk_14 = 0;
    gMtScene->unk_16 = gMtScene->fldMinorId;
    gMtScene->resManager = resrcMngCreate();

    MT_Scene_CreateResLightChar(0);
    K_Scene_InitCharLight();

    MT_Scene_CreateResLightNpc(0);
    K_Scene_InitNpcLight();

    printf("Scene data load...\n");
}

// FUN_00b5ab0
void MT_Scene_Destroy()
{
    // TODO
}

// FUN_003b5cf0
MtScene* MT_Scene_GetScene()
{
    return gMtScene;
}

// FUN_003b5d10
Resrc* MT_Scene_GetRes(u16 resTypeId)
{
    if (gMtScene->resManager == NULL)
    {
        return NULL;
    }

    return resrcMngGetRes(gMtScene->resManager, resTypeId);
}

// FUN_003b5d50
Resrc* MT_Scene_GetResListHead(u32 resType)
{
    if (gMtScene->resManager == NULL)
    {
        return NULL;
    }

    return resrcMngGetListHead(gMtScene->resManager, resType);
}

// FUN_003b5df0
u32 MT_Scene_GetTotalResInList(u32 resType)
{
    s32 i;
    s32 total;
    ResrcManager* resManager;
    u32 type;

    type = resType;
    total = 0;
    resManager = gMtScene->resManager;
    if (resManager == NULL)
    {
        return 0;
    }

    // ??? wtf is the point of this loop
    for (i = 0; i < RESRC_TYPE_MAX; i++)
    {
        if (i == type)
        {
            total += resrcMngGetTotalResInList(resManager, i);
        }
    }

    return total;
}

// FUN_003b6030
u16 MT_Scene_CreateResModelChar(u16 resId, s32 param_2, Model* mdl)
{
    ResrcManager* resManager;
    u16 resTypeId;
    ResrcModelChar* res;
    RwV3d translation = {0};

    resTypeId = RESRC_MAKE_TYPEID(resId, RESRC_TYPE_MODELCHAR);
    
    resManager = gMtScene->resManager;
    if (resManager == NULL)
    {
        printf("not found active resmanager\n");
        return 0;
    }

    if (mdl == NULL)
    {
        return 0;
    }

    res = (ResrcModelChar*)resrcMngCreateRes(resManager, resTypeId);
    if (res == NULL)
    {
        return 0;
    }

    res->mdl = mdl;
    mdlTranslate(res->mdl, &translation, rwCOMBINEREPLACE);
    RwMatrixUpdate(mdlGetMatrix(res->mdl));

    res->collisCtlTask = K_FldFrame_CreateCtlTask(NULL, resTypeId, 0, 60.0f);
    res->renderTexShadowTask = K_FldShadow_CreateRenderTexTask(res->collisCtlTask, resTypeId, param_2);

    return resTypeId;
}

// FUN_003b6270
u16 MT_Scene_CreateResModelNpc(u32 resId, u16 param_2, Model* mdl)
{
    ResrcManager* resManager;
    u16 resTypeId;
    ResrcModelNpc* res;
    RwV3d translation = {0};

    resTypeId = RESRC_MAKE_TYPEID(resId, RESRC_TYPE_MODELNPC);
    
    resManager = gMtScene->resManager;
    if (resManager == NULL)
    {
        printf("not found active resmanager\n");
        return 0;
    }

    if (mdl == NULL)
    {
        return 0;
    }

    res = (ResrcModelNpc*)resrcMngCreateRes(resManager, resTypeId);
    if (res == NULL)
    {
        return 0;
    }

    res->mdl = mdl;
    mdlTranslate(res->mdl, &translation, rwCOMBINEREPLACE);
    RwMatrixUpdate(mdlGetMatrix(res->mdl));

    res->collisCtlTask = K_FldFrame_CreateCtlTask(NULL, resTypeId, 0, 60.0f);
    res->renderTexShadowTask = K_FldShadow_CreateRenderTexTask(res->collisCtlTask, resTypeId, param_2);

    return resTypeId;
}

// FUN_003b63c0
u16 MT_Scene_CreateResLightChar(u16 resId)
{
    ResrcManager* resManager;
    u16 resTypeId;

    resTypeId = RESRC_MAKE_TYPEID(resId, RESRC_TYPE_LIGHTCHAR);

    resManager = gMtScene->resManager;
    if (resManager == NULL)
    {
        printf("not found active resmanager\n");
        return 0;
    }

    if (resrcMngCreateRes(resManager, resTypeId) == NULL)
    {
        return 0;
    }

    return resTypeId;
}

// FUN_003b6440
u16 MT_Scene_CreateResLightNpc(u16 resId)
{
    ResrcManager* resManager;
    u16 resTypeId;

    resTypeId = RESRC_MAKE_TYPEID(resId, RESRC_TYPE_LIGHTNPC);

    resManager = gMtScene->resManager;
    if (resManager == NULL)
    {
        printf("not found active resmanager\n");
        return 0;
    }

    if (resrcMngCreateRes(resManager, resTypeId) == NULL)
    {
        return 0;
    }

    return resTypeId;
}

// FUN_003b65d0
u16 MT_Scene_CreateResModelFld(u16 resId, Model* mdl)
{
    ResrcManager* resManager;
    u16 resTypeId;
    ResrcModelFld* res;
    RwV3d unused = {0};

    resTypeId = RESRC_MAKE_TYPEID(resId, RESRC_TYPE_MODELFLD);

    resManager = gMtScene->resManager;
    if (resManager == NULL)
    {
        printf("not found active resmanager\n");
        return 0;
    }

    if (mdl == NULL)
    {
        return 0;
    }

    res = (ResrcModelFld*)resrcMngCreateRes(resManager, resTypeId);
    if (res == NULL)
    {
        return 0;
    }

    res->mdl = mdl;
    res->base.flags |= (1 << 3); // 0x08

    return resTypeId;
}