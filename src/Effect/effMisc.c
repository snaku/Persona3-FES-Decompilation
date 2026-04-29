#include "Effect/effMisc.h"

static EffRandInfo sBaseRandInfo; // 00957bf0

// FUN_00357fd0. [0;16777215]
u32 effMiscRand(EffRandInfo* randInfo)
{
    // TODO

    return 0;
}

// FUN_00358030. [0.0f;1.0f[
f32 effMiscRandFloat(EffRandInfo* randInfo)
{
    return (f32)(effMiscRand(randInfo) & 0xFFFFFF) / 16777216.0f;
}

// FUN_003580b0
u32 effMiscRandRange(EffRandInfo* randInfo, u32 max)
{
    return effMiscRand(randInfo) % max;
}

// FUN_003580f0
void effMiscRandSeed(EffRandInfo* randInfo, u32 seed)
{
    // TODO
}