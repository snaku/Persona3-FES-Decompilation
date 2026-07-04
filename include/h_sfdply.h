#ifndef H_SFDPLY_H
#define H_SFDPLY_H

#include "Utils.h"

typedef struct KwlnTask KwlnTask;

// TODO
typedef enum
{
    HSFD_ORPHEUSAWAKENING = 7
} HSfdId;

// TODO
typedef enum
{
    HSFD_STATE_IDLE,
    HSFD_STATE_INIT = 2
} HSfdState;

// 544 bytes
typedef struct HSfd
{
    u8 unkData1[0x1e4];
    s16 state;          // 0x1e4. See enum 'HSfdState'
    u8 unkData2[0x04];
    u16 id;             // 0x1ea. See enum 'HSfdId'
    s16 unk_1ec;        // 0x1ec
    u16 unk_1ee;        // 0x1ee
    u8 unkData3[0x04];
    u32 isStart;        // 0x1f4
    s32 unk_1f8;        // 0x1f8
    s32 unk_1fc;        // 0x1fc
    s32 unk_200;        // 0x200
    s32 unk_204;        // 0x204
    s32 unk_208;        // 0x208
    s32 unk_20c;        // 0x20c
    u8 unkData4[0x10];
} HSfd;

KwlnTask* H_SfdPlay_CreateTaskIdle(KwlnTask* parent);

u32 H_SfdPlayCmd_CALL_MOVIE();
u32 H_SfdPlayCmd_MOVIE_SYNC();

#endif