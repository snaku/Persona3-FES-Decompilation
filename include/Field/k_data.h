#ifndef K_DATA_H
#define K_DATA_H

#include "Utils.h"

// 16 bytes
typedef struct FieldDungeonFloorData
{
    u16 majorId;
    u16 minorId;
    u8 unkData[0x0c];
} FieldDungeonFloorData;

#endif