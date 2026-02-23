#include "itfMesManager.h"
#include "Script/scr.h"

u8 ItfMesMng_CheckBmdHeaderMagic(BmdHeader* bmdHeader);

// FUN_003a2d80
ItfMes* ItfMesMng_Initialize(BmdHeader* bmdHeader)
{
    // TODO

    return NULL;
}

// FUN_003a4990
void ItfMesMng_ChangeWindowType(ItfMes* itfMes, u16 type, u32 param_3)
{
    // TODO
}

// FUN_003a5090
u8 ItfMesMng_CheckBmdHeaderMagic(BmdHeader* bmdHeader)
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