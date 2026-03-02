#include "Scene/mt_scene.h"
#include "Scene/resrcManager.h"

static MtScene sMtScene;       // 0095afc0
MtScene* gMtScene = &sMtScene; // 007cd540

// FUN_003b5cf0
MtScene* MtScene_GetScene()
{
    return gMtScene;
}

// FUN_003b5430
Resource* MtScene_GetResList(u32 resType)
{
    if (gMtScene->resManager == NULL)
    {
        return NULL;
    }

    return ResManager_GetList(gMtScene->resManager, resType);
}