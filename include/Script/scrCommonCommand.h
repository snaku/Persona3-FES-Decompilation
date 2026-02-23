#ifndef SCRCOMMONCOMMAND_H
#define SCRCOMMONCOMMAND_H

#include "Utils.h"

typedef u32 (*Scr_CmdFunc)();

// 8 bytes
typedef struct
{
    Scr_CmdFunc cmdFunc; // 0x00
    u32 totalParam;      // 0x04
} ScrCommonCommand;

typedef struct
{
    ScrCommonCommand table[502];
    s32 total;
} ScrCommonCommandData;

extern ScrCommonCommandData gScrCmdData;

#endif