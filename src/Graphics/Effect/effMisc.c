#include "Graphics/Effect/effMisc.h"

static EffRandState sRandState; // 00957bf0

// FUN_00357dd0
void effMiscQuatMultiplyVU()
{
    asm (
        vmul.xyzw vf2, vf10, vf11
        vopmula.xyz ACC, vf10, vf11
        vmaddaw.xyz ACC, vf11, vf10
        vmaddaw.xyz ACC, vf10, vf11
        vopmsub.xyz vf10, vf11, vf10
        vmulaw.w ACC, vf10, vf11
        vmsubax.w ACC, vf0, vf2
        vmsubay.w ACC, vf0, vf2
        vmsubz.w vf10, vf0, vf2
    );
}

// FUN_00357e00
void effMiscNormalizeVU()
{
    asm (
        vmul.xyzw vf2, vf10, vf10
        vaddax.w ACC, vf2, vf2
        vmadday.w ACC, vf0, vf2
        vmaddz.w vf3, vf0, vf2
        vrsqrt Q, vf0w, vf3w
        vwaitq
        vmulq.xyzw vf10, vf10, Q
    );
}

// FUN_00357fd0. [0;16777215]
u32 effMiscRand(EffRandState* state)
{
    u32 x0;
    u32 x1;
    u32 x2;
    u32 x3;
    u32 rand;

    if (state == NULL)
    {
        state = &sRandState;
    }

    x0 = state->x[0];
    x1 = state->x[1];
    x2 = state->x[2];
    x3 = state->x[3];

    rand = ((x1 << 0x02) | (((x0 >> 0x1e)) % 4)) ^ ((x3 << 0x01) | (((x2 >> 0x1f)) % 2));

    state->x[0] = rand;
    state->x[1] = x0;
    state->x[2] = x1;
    state->x[3] = x2;

    return rand;
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

    x = (x << 0x18) | (x >> 0x08);
    state->x[1] = x;

    x = x ^ 0xAA5A02FE;
    x = (x << 0x18) | (x >> 0x08);
    state->x[2] = x;

    x = x ^ 0x11BE81C7;
    state->x[3] = (x << 0x18) | (x >> 0x08);
}