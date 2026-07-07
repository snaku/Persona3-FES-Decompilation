#include "Main/OpEd/op_fade.h"
#include "Kosaka/k_assert.h"

static OpFadeWork* sWork; // 007ce3bc

// FUN_002721d0
void opFadeStart(u32 duration)
{
    OpFadeWork* work;

    K_ASSERT(sWork != NULL, 31);
    work = sWork;

    work->state = 0;
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