#ifndef ITFMESMANAGER_H
#define ITFMESMANAGER_H

#include "Utils.h"

#define BMD_HEADER_MAGIC0 0x3047534d // in little endian: "MSG0"
#define BMD_HEADER_MAGIC1 0x3147534d // in little endian: "MSG1"

// ?? bytes
typedef struct BmdHeader
{
    u8 unkData1[0x04];
    u32 size;          // size in bytes
    u32 magic;         // See 'SCR_MSG_HEADER_MAGIC0' and 'SCR_MSG_HEADER_MAGIC1'
} BmdHeader;

// 488 bytes. TODO: understand variables and find a better struct name
typedef struct ItfMes
{
    u8 unkData[0x1e8];
} ItfMes;

ItfMes* ItfMesMng_Initialize(BmdHeader* bmdHeader);
void ItfMesMng_ChangeWindowType(ItfMes* itfMes, u16 type, u32 param_3);

#endif