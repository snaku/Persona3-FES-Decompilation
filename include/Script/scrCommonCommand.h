#ifndef SCRCOMMONCOMMAND_H
#define SCRCOMMONCOMMAND_H

#include "Utils.h"

// 8 bytes
typedef struct
{
    u8 (*Scr_Cmd)(); // 0x00
    u32 totalParam;  // 0x04
} ScrCommonCommand;

#endif