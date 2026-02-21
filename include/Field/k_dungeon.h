#ifndef K_DUNGEON_H
#define K_DUNGEON_H

#include "Utils.h"

typedef struct KwlnTask KwlnTask;
typedef struct ScrHeader ScrHeader;
typedef struct FieldDungeonFloorData FieldDungeonFloorData;

typedef enum
{
    DUNGEON_STATE_IDLE = 3, // Player is exploring a floor
    DUNGEON_STATE_STOP = 9, // Destroy dungeon task
} DungeonState;

// 64 bytes
typedef struct FieldDungeon
{
    u16 state;                         // 0x00. See enum 'DungeonState'
    u32 currFloor;                     // 0x04
    s32 unk_08;                        // 0x08
    u32 shouldShutdown;                // 0x0c. If true, set state to 'DUNGEON_STATE_STOP'
    u8 unkData1[0x08];
    KwlnTask* fldRootTask;             // 0x18
    KwlnTask* eplKosakaTask;           // 0x1c
    FieldDungeonFloorData* floorsData; // 0x20. Ptr to 'gFldDngFloorsData'
    u8 unkData2[0x10];
    ScrHeader* scrHeader;              // 0x34. script header of 'DUNGEONAT.BF' or 'DUNGEONAT_AEGIS.BF' 
    u32 scrSize;                       // 0x38. Size in bytes of 'DUNGEONAT.BF' or 'DUNGEONAT_AEGIS.BF'
    s32 unk_3c;                        // 0x3c
} FieldDungeon;

void FldDungeon_RequestShutdown();
u32 FldDungeon_GetCurrentFloor();
u8 FldDungeon_IsCurrentFloorExplorable();
u16 FldDungeon_GetCurrentFloorMajorId();

#endif