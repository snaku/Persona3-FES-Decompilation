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
Resrc* MT_Scene_GetRes(u16 resTypeId)
{
    if (gMtScene->resManager == NULL)
    {
        return NULL;
    }

    return ResrcMng_GetRes(gMtScene->resManager, resTypeId);
}

// FUN_003b5d50
Resrc* MT_Scene_GetResListHead(u32 resType)
{
    if (gMtScene->resManager == NULL)
    {
        return NULL;
    }

    return ResrcMng_GetListHead(gMtScene->resManager, resType);
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
            total += ResrcMng_GetTotalResInList(resManager, i);
        }
    }

    return total;
}