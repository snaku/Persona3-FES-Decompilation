#ifndef H_FADE_H
#define H_FADE_H

#include "Utils.h"
#include "rw/rwcore.h"

typedef enum
{
    HFADE_ANMLR,
    HFADE_ANMTIME,
    HFADE_ANMAREA,
    HFADE_TRANSITION,
    HFADE_ANMMOVE,
    HFADE_TRANSITION2,
    HFADE_WHITE,
    HFADE_DAY,
    HFADE_CUSTOM, // Custom color

    HFADE_MAX
} HFadeType;

typedef enum
{
    HFADE_STATE_INIT_OUT,
    HFADE_STATE_OUT = 2,
    HFADE_STATE_HOLD,
    HFADE_STATE_INIT_IN,
    HFADE_STATE_IN = 5,
} HFadeState;

void H_Fade_ReadPak();
void H_Fade_Main();

void H_Fade_Clear();
u32 H_Fade_FadeOut();
u32 H_Fade_FadeIn();
void H_Fade_SetType(s16 type);
void H_Fade_SetCustomColor(u8 r, u8 g, u8 b);
void H_Fade_SetDuration(s16 duration);
u32 H_Fade_IsHolding();
u32 H_Fade_IsFadeOutDone();

#endif