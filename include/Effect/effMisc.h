#ifndef EFFMISC_H
#define EFFMISC_H

#include "Utils.h"

// Not really sure about the name of this file

// 16 bytes
typedef struct EffRandState
{
    u32 x[4]; // 0x00
} EffRandState;

void effMiscQuatMultiplyVU();
void effMiscNormalizeVU();

u32 effMiscRand(EffRandState* state);
f32 effMiscRandFloat(EffRandState* state);
u32 effMiscRandRange(EffRandState* state, u32 max);
void effMiscRandInit(EffRandState* state, u32 seed);

#endif