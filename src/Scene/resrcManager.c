#include "Scene/resrcManager.h"
#include "rw/rwplcore.h"
#include "temporary.h"

// FUN_003b4fc0
ResManager* ResManager_Create()
{
    ResManager* resMgr;

    resMgr = RW_MALLOC(sizeof(ResManager), 0x40000);
    memset(resMgr, 0, sizeof(ResManager));
    
    return resMgr;
}