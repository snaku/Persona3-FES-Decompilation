#ifndef MDLMANAGER_H
#define MDLMANAGER_H

#include "Utils.h"
#include "rw/rwplcore.h"

// 1072 bytes
typedef struct Model
{
    RwMatrix mat;      // 0x00
    u8 unkData1[0x94];
    u16 type;          // 0xd4
    u16 id;            // 0xd6
    u8 unkData[0x358];
} Model;

#endif