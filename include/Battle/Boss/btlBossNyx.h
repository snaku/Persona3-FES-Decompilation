#ifndef BTLBOSSNYX_H
#define BTLBOSSNYX_H

#include "temporary.h"
#include "g_data.h"

// TODO
typedef struct
{ 
    u16 sUnk1;
    Vec2f pos;
    f32 scale;
    Vec2f pos_2;
    f32 scale_2;
    Quat rot;
    f32 scale_3;
    RGBA color;
    RGBA color_2;
    RGBA color_3;
    RGBA color_4;
    RGBA color_5;
    BattleActorData* btlActor;
} NyxData;

#endif