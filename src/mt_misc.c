#include "mt_misc.h"
#include "Main/g_data.h"

// FUN_00395170
void MT_Misc_BitOn(s32 bit)
{
    datSetFlag(bit, true);
}

// FUN_003951a0
void MT_Misc_BitOff(s32 bit)
{
    datSetFlag(bit, false);
}

// FUN_003951d0
u32 MT_Misc_BitChk(s32 bit)
{
    return datGetFlag(bit) != false;
}