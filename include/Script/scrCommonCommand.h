#ifndef SCRCOMMONCOMMAND_H
#define SCRCOMMONCOMMAND_H

#include "Utils.h"

typedef u8 (*ScrCmdFunc)();

// 8 bytes
typedef struct
{
    ScrCmdFunc func; // 0x00
    u32 paramNo;     // 0x04
} ScrCommand;

typedef struct
{
    ScrCommand cmds[502];
    s32 cmdNo;
} ScrCommandTable;

extern ScrCommandTable gScrCmdTable;

#endif