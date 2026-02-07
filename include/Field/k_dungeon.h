#ifndef K_DUNGEON_H
#define K_DUNGEON_H

#include "Utils.h"

typedef struct KwlnTask KwlnTask;
typedef struct FieldDungeonFloorData FieldDungeonFloorData;

typedef enum
{
    // TODO
    DUNGEON_STATE_STOP = 9
} DungeonState;

// 64 bytes. TODO
typedef struct FieldDungeon
{
    u16 state;                         // 0x00. See enum 'DungeonState'
    u32 currFloor;                     // 0x04
    u8 unkData1[0x14];
    KwlnTask* eplKosakaTask;           // 0x1c
    FieldDungeonFloorData* floorsData; // 0x20. Ptr to 'gFldDngFloorsData'
    u8 unkData2[0x1c];
} FieldDungeon;

u32 FldDungeon_GetCurrentFloor();
u8 FldDungeon_IsCurrentFloorExplorable();

#endif