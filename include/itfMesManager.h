#ifndef ITFMESMANAGER_H
#define ITFMESMANAGER_H

#include "Utils.h"

typedef struct ScrMsgHeader ScrMsgHeader;

// 488 bytes. TODO: understand variables and find a better struct name
typedef struct ItfMes
{
    u8 unkData[0x1e8];
} ItfMes;

ItfMes* ItfMesMng_Initialize(ScrMsgHeader* scrMsgHeader);
void ItfMesMng_ChangeWindowType(ItfMes* itfMes, u16 type, u32 param_3);

#endif