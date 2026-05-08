#ifndef H_FADE_H
#define H_FADE_H

#include "Utils.h"
#include "rw/rwcore.h"

typedef enum
{
    HFADE_UNK0,
    HFADE_TIME,   // on time change
    HFADE_AREA,   // On area change
    HFADE_UNK3,
    HFADE_UNK4,
    HFADE_UNK5,   // Exactly the same as UNK3
    HFADE_WHITE,  // idk it's just a white fade
    HFADE_DAY,    // On day change
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

void H_Fade_Main();

#endif