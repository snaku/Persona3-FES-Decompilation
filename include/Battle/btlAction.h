#ifndef BTLACTION_H
#define BTLACTION_H

#include "Utils.h"
#include "g_data.h"

typedef enum
{
    BTL_ACTION_STATE_NON,
    BTL_ACTION_STATE_STANDBY,       // not his turn
    BTL_ACTION_STATE_START,         // start of the turn
    BTL_ACTION_STATE_START_HOME,    // ?
    BTL_ACTION_STATE_CHANGE_FORMA,  // ?
    BTL_ACTION_STATE_COMMAND,       // Hero can choose what he wants to do
    BTL_ACTION_STATE_TARGET,        // target mode
    BTL_ACTION_STATE_ANALYZE,      
    BTL_ACTION_STATE_AI,            // ?
    BTL_ACTION_STATE_AUTO,          // ?
    BTL_ACTION_STATE_SUPPORT,       // ?
    BTL_ACTION_STATE_BAD,
    BTL_ACTION_STATE_READY,
    BTL_ACTION_STATE_MOVE_TARGET,
    BTL_ACTION_STATE_MOVE_HOME,
    BTL_ACTION_STATE_ATTACK,
    BTL_ACTION_STATE_SKILL,
    BTL_ACTION_STATE_REINFORCE,
    BTL_ACTION_STATE_SUMMON,
    BTL_ACTION_STATE_ASSIST,
    BTL_ACTION_STATE_EVENT,
    BTL_ACTION_STATE_ERROR,
    BTL_ACTION_STATE_ENDURE,
    BTL_ACTION_STATE_WAIT,
    BTL_ACTION_STATE_PERSONA,
    BTL_ACTION_STATE_BAD_DMG,
    BTL_ACTION_STATE_ESCAPE_MES,
    BTL_ACTION_STATE_ESCAPE,
    BTL_ACTION_STATE_ROUNDUP_MES,
    BTL_ACTION_STATE_ROUNDUP,
    BTL_ACTION_STATE_PACKET,
    BTL_ACTION_STATE_END,
    BTL_ACTION_STATE_END_HOME,
    BTL_ACTION_STATE_DEAD,
    BTL_ACTION_STATE_EXIT,
    BTL_ACTION_STATE_TEST
} BattleActionState;

typedef struct
{
    BattleActorData* btlActor; // 0xa2c
} BtlActionUnkStruct;

// TODO
typedef struct 
{
    u16 currState;                  // 0xc
    u16 unk_0e;                     // 0e
    u16 oldState;                   // 0x10
    u32 unk_14;                     // 0x14
    u32 unk_18;                     // 0x18
    u32 unkTimer;                   // 0x1c. Resets on state change
    u32 unk_20;                     // 0x20
    u32 idleWeaponAnimTimer;        // 0x24. Decrement every frame. If underflow, play animation
    BtlActionUnkStruct* unkStruct1; // 0x28
} BattleActionStruct;

#endif