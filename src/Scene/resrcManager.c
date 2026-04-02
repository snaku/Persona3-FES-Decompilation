#include "Scene/resrcManager.h"
#include "rw/rwplcore.h"
#include "Model/mdlManager.h"
#include "temporary.h"
#include "g_data.h"

// FUN_003b4fc0
ResrcManager* ResrcMng_Init()
{
    ResrcManager* resMgr;

    resMgr = RW_MALLOC(sizeof(ResrcManager), 0x40000);
    memset(resMgr, 0, sizeof(ResrcManager));
    
    return resMgr;
}

// FUN_003b5020
void ResrcMng_Destroy(ResrcManager* resManager)
{
    s32 i;
    Resrc* currList;

    if (resManager != NULL)
    {
        for (i = 0; i < RESRC_TYPE_MAX; i++)
        {
            currList = ResrcMng_GetListHead(resManager, i);

            while (currList != NULL)
            {
                ResrcMng_DestroyRes(resManager, currList);

                currList = ResrcMng_GetListHead(resManager, i);
            }
        }

        RW_FREE(resManager);
    }
}

// FUN_003b50d0
Resrc* ResrcMng_CreateRes(ResrcManager* resManager, u16 resTypeId)
{
    // TODO

    return NULL;
}

// FUN_003b5360
void ResrcMng_DestroyRes(ResrcManager* resManager, Resrc* res)
{
    // TODO
}

// FUN_003b5430. Return the head of a list of a resource type
Resrc* ResrcMng_GetListHead(ResrcManager* resManager, u8 resType)
{
    if (resType >= RESRC_TYPE_MAX)
    {
        return NULL;
    }

    return resManager->resLists[resType];
}

// FUN_003b5460. Return the tail of a list of a resource type
Resrc* ResrcMng_GetListTail(ResrcManager* resManager, u8 resType)
{
    Resrc* currRes;
    
    if (resType >= RESRC_TYPE_MAX)
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
Resrc* ResrcMng_GetRes(ResrcManager* resManager, u16 resTypeId)
{
    u8 type;
    Resrc* currRes;

    type = RES_GET_TYPE(resTypeId);
    if (type == 0)
    {
        return NULL;
    }

    if (type >= RESRC_TYPE_MAX)
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
u32 ResrcMng_GetTotalResInList(ResrcManager* resManager, u8 resType)
{
    u32 total;
    Resrc* currRes;

    total = 0;
    if (resType >= RESRC_TYPE_MAX)
    {
        return total;
    }

    for (currRes = resManager->resLists[resType]; currRes != NULL; currRes = currRes->next)
    {
        total++;
    }

    return total;
}