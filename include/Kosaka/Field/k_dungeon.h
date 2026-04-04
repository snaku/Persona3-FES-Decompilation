#ifndef K_DUNGEON_H
#define K_DUNGEON_H

#include "Utils.h"

typedef struct KwlnTask KwlnTask;
typedef struct HCdvd HCdvd;
typedef struct Model Model;
typedef struct FldDungeonFloorData FldDungeonFloorData;

typedef enum
{
    FLDDUNGEON_STATE_IDLE = 3, // Player is exploring a floor
    FLDDUNGEON_STATE_STOP = 9, // Destroy dungeon task
} FldDungeonState;

// 64 bytes
typedef struct FldDungeon
{
    u16 state;                       // 0x00. See enum 'FldDungeonState'
    u32 currFloor;                   // 0x04
    s32 unk_08;                      // 0x08
    u32 shouldShutdown;              // 0x0c. If true, set state to 'DUNGEON_STATE_STOP'
    s32 unk_10;                      // 0x10
    HCdvd* scrCdvd;                  // 0x14
    KwlnTask* fldRootTask;           // 0x18
    KwlnTask* eplKosakaTask;         // 0x1c
    FldDungeonFloorData* floorsData; // 0x20. Ptr to 'gFldDngFloorsData'
    u8 unkData2[0x10];
    void* scrMemory;                 // 0x34. script memory of 'DUNGEONAT.BF' or 'DUNGEONAT_AEGIS.BF'
    u32 scrSize;                     // 0x38. Size in bytes of 'DUNGEONAT.BF' or 'DUNGEONAT_AEGIS.BF'
    s32 unk_3c;                      // 0x3c
} FldDungeon;

extern KwlnTask* gDungeonTask;
extern Model* gDungeonTpMdl;

KwlnTask* K_FldDungeon_CreateTask(KwlnTask* parentTask, u32 floor, u32 param_3);
void K_FldDungeon_RequestShutdown();
u32 K_FldDungeon_GetCurrentFloor();
u8 K_FldDungeon_IsCurrentFloorExplorable();
FldDungeonFloorData* K_FldDungeon_GetCurrentFloorData();
void* K_FldDungeon_GetScrMemory();
u32 K_FldDungeon_GetScrSize();
HCdvd* K_FldDungeon_RequestBlockScript(u32 blockId);

#endif