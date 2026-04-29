#ifndef EFFMISC_H
#define EFFMISC_H

#include "Utils.h"

// Not really sure about the name of this file

// 16 bytes
typedef struct EffRandInfo
{
    u32 seed;   // 0x00
    u32 unk_04; // 0x04
    u32 unk_08; // 0x08
    u32 unk_0c; // 0x0c
} EffRandInfo;

u32 effMiscRand(EffRandInfo* randInfo);
f32 effMiscRandFloat(EffRandInfo* randInfo);
u32 effMiscRandRange(EffRandInfo* randInfo, u32 max);
void effMiscRandSeed(EffRandInfo* randInfo, u32 seed);

#endif