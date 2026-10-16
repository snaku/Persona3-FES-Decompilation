#ifndef EFFMISC_H
#define EFFMISC_H

#include "Utils.h"
#include "rw/rwcore.h"

// Not really sure about the name of this file

// 16 bytes
typedef struct EffRandState
{
    u32 x[4]; // 0x00
} EffRandState;

// 8 bytes
typedef struct EffMiscRenderStateEntry
{
    RwRenderState state; // 0x00
    u32 value;           // 0x04
} EffMiscRenderStateEntry;

void effMiscQuatMultiplyVU();
void effMiscNormalizeVU();

u32 effMiscRand(EffRandState* state);
f32 effMiscRandFloat(EffRandState* state);
u32 effMiscRandRange(EffRandState* state, u32 max);
void effMiscRandInit(EffRandState* state, u32 seed);

#endif