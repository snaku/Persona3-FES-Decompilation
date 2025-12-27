#ifndef BTLACTOR_H
#define BTLACTOR_H

#include "g_data.h"

typedef struct
{
    BattleActorData* actorData;
} BattleActorUnkStruct;

// TODO. Really not sure of this name. 1200 bytes
typedef struct 
{
    // data before...
    u32 unk_08;                     // 0x8
    // data inbetween...
    u16 currState;                  // 0xc
    u16 unk_0e;                     // 0xe
    u16 oldState;                   // 0x10
    u32 unk_14;                     // 0x14
    u32 unk_18;                     // 0x18
    u32 unkTimer;                   // 0x1c. Resets on state change
    u32 unk_20;                     // 0x20
    u32 idleWeaponAnimTimer;        // 0x24. Decrement every frame. If underflow, play animation
    BattleActorUnkStruct* unkStruct1; // 0x28
    // data inbetween...
    u16 unk_36;                     // 0x36
    // data inbetween...
    BattleActor* prev;       // 0x95
    // data inbetween...
    BattleActor* next;       // 0x4a4
} BattleActor; 

#endif