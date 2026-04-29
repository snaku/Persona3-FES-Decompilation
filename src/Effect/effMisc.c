#include "Effect/effMisc.h"

static EffRandState sRandState; // 00957bf0

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
u32 effMiscRand(EffRandState* state)
{
    // TODO

    return 0;
}

// FUN_00358030. [0.0f;1.0f[
f32 effMiscRandFloat(EffRandState* state)
{
    return (f32)(effMiscRand(state) & 0xFFFFFF) / 16777216.0f;
}

// FUN_003580b0. [0;max[
u32 effMiscRandRange(EffRandState* state, u32 max)
{
    return effMiscRand(state) % max;
}

// FUN_003580f0
void effMiscRandInit(EffRandState* state, u32 seed)
{
    u32 x;

    if (state == NULL)
    {
        state = &sRandState;
    }

    x = seed ^ 0xAED1A0C;
    state->x[0] = x;

    x = (x << 0x18) | (x >> 8);
    state->x[1] = x;

    x = x ^ 0xAA5A02FE;
    x = (x << 0x18) | (x >> 8);
    state->x[2] = x;

    x = x ^ 0x11BE81C7;
    state->x[3] = (x << 0x18) | (x >> 8);
}