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

// FUN_003b5020
void ResManager_Destroy(ResManager* resManager)
{
    s32 i;
    Resource* currList;

    if (resManager != NULL)
    {
        for (i = 0; i < RES_TYPE_MAX; i++)
        {
            currList = ResManager_GetListHead(resManager, i);

            while (currList != NULL)
            {
                ResManager_DestroyRes(resManager, currList);

                currList = ResManager_GetListHead(resManager, i);
            }
        }

        RW_FREE(resManager);
    }
}

// FUN_003b5360
void ResManager_DestroyRes(ResManager* resManager, Resource* res)
{
    // TODO
}

// FUN_003b5430. Return the head of a list of a resource type
Resource* ResManager_GetListHead(ResManager* resManager, u8 resType)
{
    if (resType >= RES_TYPE_MAX)
    {
        return NULL;
    }

    return resManager->resLists[resType];
}

// FUN_003b5460. Return the tail of a list of a resource type
Resource* ResManager_GetListTail(ResManager* resManager, u8 resType)
{
    Resource* currRes;
    
    if (resType >= RES_TYPE_MAX)
    {
        return NULL;
    }

    currRes = resManager->resLists[resType];
    if (currRes == NULL)
    {
        return currRes;
    }

    while (currRes->next != NULL)
    {
        currRes = currRes->next;
    }

    return currRes;
}

// FUN_003b54c0. Return a resource by a resTypeId
Resource* ResManager_GetRes(ResManager* resManager, u16 resTypeId)
{
    u8 type;
    Resource* currRes;

    type = RES_GET_TYPE(resTypeId);
    if (type == 0)
    {
        return NULL;
    }

    if (type >= RES_TYPE_MAX)
    {
        return NULL;
    }

    for (currRes = resManager->resLists[type]; currRes != NULL; currRes = currRes->next)
    {
        if (currRes->resTypeId == resTypeId)
        {
            return currRes;
        }
    }

    return NULL;
}

// FUN_003b5550. Return the total number of resource in a list by a resType
u32 ResManager_GetTotalResInList(ResManager* resManager, u8 resType)
{
    u32 total;
    Resource* currRes;

    total = 0;
    if (resType >= RES_TYPE_MAX)
    {
        return total;
    }

    for (currRes = resManager->resLists[resType]; currRes != NULL; currRes = currRes->next)
    {
        total++;
    }

    return total;
}