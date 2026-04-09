#include "itfMesManager.h"
#include "Script/scr.h"

u8 itfMesMngCheckBmdMagic(BmdHeader* bmdHeader);

// FUN_003a2d80
s32 itfMesMngInitialize(BmdHeader* bmdHeader)
{
    // TODO

    return 0;
}

// FUN_003a3060
void itfMesMngDestroyHandle(s32 mesHandleIdx)
{
    // TODO
}

// FUN_003a4990
void itfMesMngChangeWindowType(s32 mesHandleIdx, u16 type, u32 param_3)
{
    // TODO
}

// FUN_003a5090
u8 itfMesMngCheckBmdMagic(BmdHeader* bmdHeader)
{
    s8 isMagicValid;

    isMagicValid = true;
    switch (bmdHeader->magic)
    {
        case BMD_HEADER_MAGIC1:
        case BMD_HEADER_MAGIC0: break;

        default: isMagicValid = false;
    }
    
    if (isMagicValid)
    {
        return true;
    }
    
    return false;
}