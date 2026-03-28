#ifndef K_DUNGEON_H
#define K_DUNGEON_H

#include "Utils.h"

typedef struct KwlnTask KwlnTask;
typedef struct K_FieldDungeonFloorData K_FieldDungeonFloorData;
typedef struct H_Cdvd H_Cdvd;
typedef struct Model Model;

typedef enum
{
    DUNGEON_STATE_IDLE = 3, // Player is exploring a floor
    DUNGEON_STATE_STOP = 9, // Destroy dungeon task
} DungeonState;

// 64 bytes
typedef struct K_FieldDungeon
{
    u16 state;                           // 0x00. See enum 'DungeonState'
    u32 currFloor;                       // 0x04
    s32 unk_08;                          // 0x08
    u32 shouldShutdown;                  // 0x0c. If true, set state to 'DUNGEON_STATE_STOP'
    s32 unk_10;                          // 0x10
    H_Cdvd* scrCdvd;                     // 0x14
    KwlnTask* fldRootTask;               // 0x18
    KwlnTask* eplKosakaTask;             // 0x1c
    K_FieldDungeonFloorData* floorsData; // 0x20. Ptr to 'gFldDngFloorsData'
    u8 unkData2[0x10];
    void* scrMemory;                     // 0x34. script memory of 'DUNGEONAT.BF' or 'DUNGEONAT_AEGIS.BF'
    u32 scrSize;                         // 0x38. Size in bytes of 'DUNGEONAT.BF' or 'DUNGEONAT_AEGIS.BF'
    s32 unk_3c;                          // 0x3c
} K_FieldDungeon;

extern KwlnTask* gDungeonTask;
extern Model* gDungeonTpMdl;

KwlnTask* K_FldDungeon_CreateTask(KwlnTask* parentTask, u32 floor, u32 param_3);
void K_FldDungeon_RequestShutdown();
u32 K_FldDungeon_GetCurrentFloor();
u8 K_FldDungeon_IsCurrentFloorExplorable();
K_FieldDungeonFloorData* K_FldDungeon_GetCurrentFloorData();
void* K_FldDungeon_GetScrMemory();
u32 K_FldDungeon_GetScrSize();
H_Cdvd* K_FldDungeon_RequestBlockScript(u32 blockId);

#endif