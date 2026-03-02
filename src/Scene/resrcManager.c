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

// FUN_003b5430. Return the head of a list of a resource type
Resource* ResManager_GetList(ResManager* resManager, u8 resType)
{
    if (resType >= RES_TYPE_MAX)
    {
        return NULL;
    }

    return resManager->resLists[resType];
}