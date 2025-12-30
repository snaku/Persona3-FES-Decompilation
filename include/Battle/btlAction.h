#ifndef BTLACTION_H
#define BTLACTION_H

typedef enum
{
    BTL_ACTION_STATE_NON,           // base state when a BattleActor is created
    BTL_ACTION_STATE_STANDBY,       // not his turn
    BTL_ACTION_STATE_START,         // start of the turn
    BTL_ACTION_STATE_START_HOME,    // ?
    BTL_ACTION_STATE_CHANGE_FORMA,  // ?
    BTL_ACTION_STATE_COMMAND,       // Hero can choose what he wants to do
    BTL_ACTION_STATE_TARGET,        // target mode
    BTL_ACTION_STATE_ANALYZE,       // viewing analyze menu
    BTL_ACTION_STATE_AI,            // ?
    BTL_ACTION_STATE_AUTO,          // rush
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
    BTL_ACTION_STATE_BAD_DMG,       // Miss attack ?
    BTL_ACTION_STATE_ESCAPE_MES,
    BTL_ACTION_STATE_ESCAPE,
    BTL_ACTION_STATE_ROUNDUP_MES,   // showing all-out attack message
    BTL_ACTION_STATE_ROUNDUP,       // currently doing an all-out attack
    BTL_ACTION_STATE_PACKET,
    BTL_ACTION_STATE_END,
    BTL_ACTION_STATE_END_HOME,
    BTL_ACTION_STATE_DEAD,
    BTL_ACTION_STATE_EXIT,
    BTL_ACTION_STATE_TEST
} BattleActionState;

typedef struct
{
    void (*BtlAction_InitState)(BattleActor* btlActor);
    void (*BtlAction_UpdateState)(BattleActor* btlActor);
    const char* name;
} BattleActionStateEntry;

extern u32 gUnk_007cc530;
extern BattleActionStateEntry gActionStateTable[];

void BtlAction_SetStateAndInit(BattleActor* btlActor, u16 btlState);

#endif