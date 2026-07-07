#include "Main/OpEd/op_fade.h"
#include "Kosaka/k_assert.h"

static OpFadeWork* sWork; // 007ce3bc

// FUN_002721d0
void opFadeStart(u32 duration)
{
    OpFadeWork* work;

    K_ASSERT(sWork != NULL, 31);
    work = sWork;

    work->state = OPFADE_STATE_START;
    work->duration = duration;
}

// FUN_00272220
void opFadeSetColor(const RwRGBA* color)
{
    OpFadeWork* work;

    K_ASSERT(sWork != NULL, 31);
    work = sWork;

    work->color = *color;
}

// FUN_00272290
void opFadeIn()
{
    OpFadeWork* work;

    K_ASSERT(sWork != NULL, 31);
    work = sWork;

    work->state = OPFADE_STATE_IN;
    work->timer = work->duration;
}

// FUN_002722e0
void opFadeOut()
{
    OpFadeWork* work;

    K_ASSERT(sWork != NULL, 31);
    work = sWork;

    work->state = OPFADE_STATE_OUT;
    work->timer = work->duration;
}