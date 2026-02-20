#ifndef BTLACTOR_H
#define BTLACTOR_H

#include "datUnit.h"

typedef struct BattleActor BattleActor;
typedef struct BattleActorCore BattleActorCore;
typedef struct UnitData UnitData;

// TODO. This struct contains the pos, rot and scale (and other unknown things) of the actor
// temporary name maybe ?
struct BattleActorCore 
{
    // data before...
    u32 unkFlag_9c;                    // 0x9c
    // data inbetween...
    UnitData* unit; // 0xa2c
};

// TODO. 1200 bytes
struct BattleActor
{
    u8 unkData1[0x08];
    u32 actorId;                // 0x8
    u16 currState;              // 0xc. See enum 'BattleActionState'
    u16 pendingState;           // 0xe. See enum 'BattleActionState'
    u16 oldState;               // 0x10
    u16 pendingStateTimer;      // 0x12. If > 0, decrement every frame and if == 0, new state will be pendingState
    u16 unk_14;                 // 0x14
    s16 unk_16;                 // 0x16
    u16 unk_18;                 // 0x18
    u16 unk_1a;                 // 0x1a
    u32 stateTimer;             // 0x1c. 60hz timer (+=2 per frame at 30fps). Reset on state change
    u32 unk_20;                 // 0x20
    u32 idleWeaponAnimTimer;    // 0x24. Decrement every frame. If underflow, play animation
    u8 unkData1[0x08];
    BattleActorCore* actorCore; // 0x30
    s16 unk_34;                 // 0x34
    u16 unk_36;                 // 0x36
    u8 unkData1[0x46c];
    BattleActor* next;          // 0x4a4
    BattleActor* prev;          // 0x4a8
    s32 unk_4ac;                // 0x4ac
};

#endif