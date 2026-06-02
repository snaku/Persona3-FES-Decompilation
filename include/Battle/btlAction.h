#ifndef BTLACTION_H
#define BTLACTION_H

#include "Battle/btlTarget.h"

typedef struct BtlUnit BtlUnit;

typedef enum
{
    BTLACTION_STATE_NON,
    BTLACTION_STATE_STANDBY,
    BTLACTION_STATE_START,
    BTLACTION_STATE_STARTHOME,
    BTLACTION_STATE_CHANGEFORMA,
    BTLACTION_STATE_COMMAND,
    BTLACTION_STATE_TARGET,
    BTLACTION_STATE_ANALYZE,
    BTLACTION_STATE_AI,
    BTLACTION_STATE_AUTO,
    BTLACTION_STATE_SUPPORT,
    BTLACTION_STATE_BAD,
    BTLACTION_STATE_READY,
    BTLACTION_STATE_MOVETARGET,
    BTLACTION_STATE_MOVEHOME,
    BTLACTION_STATE_ATTACK,
    BTLACTION_STATE_SKILL,
    BTLACTION_STATE_REINFORCE,
    BTLACTION_STATE_SUMMON,
    BTLACTION_STATE_ASSIST,
    BTLACTION_STATE_EVENT,
    BTLACTION_STATE_ERROR,
    BTLACTION_STATE_ENDURE,
    BTLACTION_STATE_WAIT,
    BTLACTION_STATE_PERSONA,
    BTLACTION_STATE_BADDMG,
    BTLACTION_STATE_ESCAPEMES,
    BTLACTION_STATE_ESCAPE,
    BTLACTION_STATE_ROUNDUPMES,
    BTLACTION_STATE_ROUNDUP,
    BTLACTION_STATE_PACKET,
    BTLACTION_STATE_END,
    BTLACTION_STATE_ENDHOME,
    BTLACTION_STATE_DEAD,
    BTLACTION_STATE_EXIT,
    BTLACTION_STATE_TEST
} BtlActionState;

typedef struct BtlAction BtlAction;

// 1200 bytes
struct BtlAction
{
    u64 uid;                 // 0x00
    u32 id;                  // 0x08
    u16 currState;           // 0x0c. See enum 'BtlActionState'
    u16 pendingState;        // 0x0e. See enum 'BtlActionState'
    u16 oldState;            // 0x10
    u16 pendingStateTimer;   // 0x12
    u16 unk_14;              // 0x14
    s16 unk_16;              // 0x16
    u16 unk_18;              // 0x18
    u16 unk_1a;              // 0x1a
    u32 stateTimer;          // 0x1c
    u32 unk_20;              // 0x20
    s32 idleWeaponAnimTimer; // 0x24
    s32 unk_28;              // 0x28
    s32 unk_2c;              // 0x2c
    BtlUnit* unit;           // 0x30
    s16 unk_34;              // 0x34
    u16 rand;                // 0x36
    BtlTarget target;        // 0x38
    u8 unkData3[0x3fc];
    s32 unk_484;             // 0x484
    u8 unkData4[0x14];
    u16 stateAfterEvt;       // 0x49c
    u32 (*evtFunc)();        // 0x4a0
    BtlAction* next;         // 0x4a4
    BtlAction* prev;         // 0x4a8
    s32 unk_4ac;             // 0x4ac
};

u32 btlActionIdleWeaponAnim(BtlAction* action);
BtlAction* btlActionCreate();
void btlActionSetState(BtlAction* action, u16 state);
void btlActionUpdateAll();
void btlActionDestroyAll();
BtlAction* btlActionFindByUnit(BtlUnit* unit);
BtlAction* btlActionFindById(u32 id);

#endif