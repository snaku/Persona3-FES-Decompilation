#ifndef SCRCOMMONCOMMAND_H
#define SCRCOMMONCOMMAND_H

#include "Utils.h"

typedef u32 (*ScrCmdFunc)();

// 8 bytes
typedef struct
{
    ScrCmdFunc func; // 0x00
    u32 paramCount;  // 0x04
} ScrCommand;

// 4020 bytes
typedef struct
{
    ScrCommand cmds[502]; // 0x00
    s32 count;            // 0xfb0
} ScrCommandTable;

extern ScrCommandTable gScrCmdTable;

#endif