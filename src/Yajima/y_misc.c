#include "Yajima/y_misc.h"
#include "sce/eeregs.h"

// FUN_004241d0
u32 Y_Misc_GetT0Count()
{
    return DGET_T0_COUNT();
}