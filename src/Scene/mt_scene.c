#include "Scene/mt_scene.h"
#include "Scene/resrcManager.h"

static MtScene sMtScene;       // 0095afc0
MtScene* gMtScene = &sMtScene; // 007cd540

// FUN_003b5cf0
MtScene* MT_Scene_GetScene()
{
    return gMtScene;
}

// FUN_003b5d10
Resource* MT_Scene_GetRes(u16 resTypeId)
{
    if (gMtScene->resManager == NULL)
    {
        return NULL;
    }

    return ResManager_GetRes(gMtScene->resManager, resTypeId);
}

// FUN_003b5d50
Resource* MT_Scene_GetResList(u32 resType)
{
    if (gMtScene->resManager == NULL)
    {
        return NULL;
    }

    return ResManager_GetList(gMtScene->resManager, resType);
}