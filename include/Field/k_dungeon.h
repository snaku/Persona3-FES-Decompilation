#ifndef K_DUNGEON_H
#define K_DUNGEON_H

#include "Utils.h"

typedef struct KwlnTask KwlnTask;
typedef struct FieldDungeonFloorData FieldDungeonFloorData;

typedef enum
{
    DUNGEON_STATE_IDLE = 3, // Player is exploring a floor
    DUNGEON_STATE_STOP = 9, // Destroy dungeon task
} DungeonState;

// 64 bytes. TODO
typedef struct FieldDungeon
{
    u16 state;                         // 0x00. See enum 'DungeonState'
    u32 currFloor;                     // 0x04
    u8 unkData1[0x10];
    KwlnTask* fldRootTask;             // 0x18
    KwlnTask* eplKosakaTask;           // 0x1c
    FieldDungeonFloorData* floorsData; // 0x20. Ptr to 'gFldDngFloorsData'
    u8 unkData2[0x1c];
} FieldDungeon;

u32 FldDungeon_GetCurrentFloor();
u8 FldDungeon_IsCurrentFloorExplorable();

#endif