#include "Scene/resrcManager.h"
#include "rw/rwplcore.h"
#include "temporary.h"

// FUN_003b4fc0
ResManager* ResManager_Init()
{
    ResManager* resMgr;

    resMgr = RW_MALLOC(sizeof(ResManager), 0x40000);
    memset(resMgr, 0, sizeof(ResManager));
    
    return resMgr;
}

// FUN_003b5360
void ResManager_DestroyRes(ResManager* resManager, Resource* res)
{
    // TODO
}

// FUN_003b5430. Return the head of a list of a resource type
Resource* ResManager_GetList(ResManager* resManager, u8 resType)
{
    if (resType >= RES_TYPE_MAX)
    {
        return NULL;
    }

    return resManager->resLists[resType];
}

// FUN_003b5020
void ResManager_Destroy(ResManager* resManager)
{
    s32 i;
    Resource* currList;

    if (resManager != NULL)
    {
        for (i = 0; i < RES_TYPE_MAX; i++)
        {
            currList = ResManager_GetList(resManager, i);

            while (currList != NULL)
            {
                ResManager_DestroyRes(resManager, currList);

                currList = ResManager_GetList(resManager, i);
            }
        }

        RW_FREE(resManager);
    }
}