#ifndef K_DATA_H
#define K_DATA_H

#include "Utils.h"

// 16 bytes
typedef struct FldDungeonFloorData
{
    u16 majorId;        // 0x00
    u16 minorId;        // 0x02
    u8 unkData1[0x08];
    u8 blockId;         // 0x0c. Tartarus block
    u8 unkData[0x04];
} FldDungeonFloorData;

extern u32 gTraceCode;
extern void* gFldScrMemory;
extern u32 gFldScrSize;

extern FldDungeonFloorData gFldDngFloorsData[500];

void K_Data_LoadFldMainScript();
void K_Data_LoadDngFloorsData(u32 scenarioMode);

#endif