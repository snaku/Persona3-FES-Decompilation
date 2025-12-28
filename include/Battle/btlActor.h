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
    u16 pendingState;               // 0xe
    u16 oldState;                   // 0x10
    u16 stateTimer;                 // 0x12. If > 0, decrement every frame and if == 0, new state will be pendingState
    u16 unk_14;                     // 0x14
    u32 unk_18;                     // 0x18
    u32 unkTimer;                   // 0x1c. Resets on state change
    u32 unk_20;                     // 0x20
    u32 idleWeaponAnimTimer;        // 0x24. Decrement every frame. If underflow, play animation
    BattleActorUnkStruct* unkStruct1; // 0x28
    // data inbetween...
    u16 unk_36;                     // 0x36
    // data inbetween...
    BattleActor* next;       // 0x4a4
    BattleActor* prev;       // 0x4a8
} BattleActor; 

#endif