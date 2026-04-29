#include "Effect/effMisc.h"

static EffRandInfo sBaseRandInfo; // 00957bf0

// FUN_00357e00
void effMiscNormalizeVU()
{
    __asm__ volatile (
        ".set noreorder            \n"
        "vmul.xyzw vf2, vf10, vf10 \n"
        "vaddax.w ACC, vf2, vf2    \n"
        "vmadday.w ACC, vf0, vf2   \n"
        "vmaddz.w vf3, vf0, vf2    \n"
        "vrsqrt Q, vf0, vf3        \n"
        "vwaitq                    \n"
        "vmulq.xyzw vf10, vf10, Q  \n"
        ".set reorder"
        :
        :
        : "vf2", "vf3", "ACC", "Q", "memory"
    );
}

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

// FUN_003580b0. [0;max[
u32 effMiscRandRange(EffRandInfo* randInfo, u32 max)
{
    return effMiscRand(randInfo) % max;
}

// FUN_003580f0
void effMiscRandSeed(EffRandInfo* randInfo, u32 seed)
{
    // TODO
}