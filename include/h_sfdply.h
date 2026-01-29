#ifndef H_SFDPLY_H
#define H_SFDPLY_H

#include "Utils.h"

typedef struct KwlnTask KwlnTask;

// 544 bytes
typedef struct SfdPlay
{
    u8 unkData1[0x1ea];
    s16 unk_1ea;        // 0x1ea
    u8 unkData2[0x08];
    s32 unk_1f4;        // 0x1f4
    s32 unk_1f8;        // 0x1f8
    s32 unk_1fc;        // 0x1fc
    u8 unkData3[0x20];
} SfdPlay;

#endif