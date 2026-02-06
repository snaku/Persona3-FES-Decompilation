#ifndef K_DUNGEON_H
#define K_DUNGEON_H

#include "Utils.h"

typedef struct KwlnTask KwlnTask;

typedef enum
{
    // TODO
    DUNGEON_STATE_STOP = 9
} DungeonState;

// 64 bytes. TODO
typedef struct DungeonData
{
    u16 state;               // 0x00
    u32 currFloor;           // 0x04
    u8 unkData1[0x14];
    KwlnTask* eplKosakaTask; // 0x1c
    u8 unkData2[0x20];
} DungeonData;

u32 Dungeon_GetCurrentFloor();
u8 Dungeon_IsCurrentFloorExplorable();

#endif