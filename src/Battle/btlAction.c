#include "Battle/btlAction.h"
#include "datCalc.h"

void BtlAction_InitStateNon(BattleActionStruct* btlAction);
void BtlAction_UpdateStateNon(BattleActionStruct* btlAction);
void BtlAction_InitStateStandBy(BattleActionStruct* btlAction);
void BtlAction_UpdateStateStandBy(BattleActionStruct* btlAction);
void BtlAction_InitStateStart(BattleActionStruct* btlAction);
void BtlAction_UpdateStateStart(BattleActionStruct* btlAction);
void BtlAction_InitStateStartHome(BattleActionStruct* btlAction);
void BtlAction_UpdateStateStartHome(BattleActionStruct* btlAction);
void BtlAction_InitStateChangeFormation(BattleActionStruct* btlAction);
void BtlAction_UpdateStateChangeFormation(BattleActionStruct* btlAction);
void BtlAction_InitStateCommand(BattleActionStruct* btlAction);
void BtlAction_UpdateStateCommand(BattleActionStruct* btlAction);
void BtlAction_InitStateTarget(BattleActionStruct* btlAction);
void BtlAction_UpdateStateTarget(BattleActionStruct* btlAction);
void BtlAction_InitStateAnalyze(BattleActionStruct* btlAction);
void BtlAction_UpdateStateAnalyze(BattleActionStruct* btlAction);
void BtlAction_InitStateAI(BattleActionStruct* btlAction);
void BtlAction_UpdateStateAI(BattleActionStruct* btlAction);
void BtlAction_InitStateAuto(BattleActionStruct* btlAction);
void BtlAction_UpdateStateAuto(BattleActionStruct* btlAction);
void BtlAction_InitStateSupport(BattleActionStruct* btlAction);
void BtlAction_UpdateStateSupport(BattleActionStruct* btlAction);
void BtlAction_InitStateBad(BattleActionStruct* btlAction);
void BtlAction_UpdateStateBad(BattleActionStruct* btlAction);
void BtlAction_InitStateReady(BattleActionStruct* btlAction);
void BtlAction_UpdateStateReady(BattleActionStruct* btlAction);
void BtlAction_InitStateMoveTarget(BattleActionStruct* btlAction);
void BtlAction_UpdateStateMoveTarget(BattleActionStruct* btlAction);
void BtlAction_InitStateMoveHome(BattleActionStruct* btlAction);
void BtlAction_UpdateStateMoveHome(BattleActionStruct* btlAction);
void BtlAction_InitStateAttack(BattleActionStruct* btlAction);
void BtlAction_UpdateStateAttack(BattleActionStruct* btlAction);
void BtlAction_InitStateSkill(BattleActionStruct* btlAction);
void BtlAction_UpdateStateSkill(BattleActionStruct* btlAction);
void BtlAction_InitStateReinforce(BattleActionStruct* btlAction);
void BtlAction_UpdateStateReinforce(BattleActionStruct* btlAction);
void BtlAction_InitStateSummon(BattleActionStruct* btlAction);
void BtlAction_UpdateStateSummon(BattleActionStruct* btlAction);
void BtlAction_InitStateAssist(BattleActionStruct* btlAction);
void BtlAction_UpdateStateAssist(BattleActionStruct* btlAction);
void BtlAction_InitStateEvent(BattleActionStruct* btlAction);
void BtlAction_UpdateStateEvent(BattleActionStruct* btlAction);
void BtlAction_InitStateError(BattleActionStruct* btlAction);
void BtlAction_UpdateStateError(BattleActionStruct* btlAction);
void BtlAction_InitStateEndure(BattleActionStruct* btlAction);
void BtlAction_UpdateStateEndure(BattleActionStruct* btlAction);
void BtlAction_InitStateWait(BattleActionStruct* btlAction);
void BtlAction_UpdateStateWait(BattleActionStruct* btlAction);
void BtlAction_InitStatePersona(BattleActionStruct* btlAction);
void BtlAction_UpdateStatePersona(BattleActionStruct* btlAction);
void BtlAction_InitStateBadDamage(BattleActionStruct* btlAction);
void BtlAction_UpdateStateBadDamage(BattleActionStruct* btlAction);
void BtlAction_InitStateEscapeMes(BattleActionStruct* btlAction);
void BtlAction_UpdateStateEscapeMes(BattleActionStruct* btlAction);
void BtlAction_InitStateEscape(BattleActionStruct* btlAction);
void BtlAction_UpdateStateEscape(BattleActionStruct* btlAction);
void BtlAction_InitStateRoundUpMes(BattleActionStruct* btlAction);
void BtlAction_UpdateStateRoundUpMes(BattleActionStruct* btlAction);
void BtlAction_InitStateRoundUp(BattleActionStruct* btlAction);
void BtlAction_UpdateStateRoundUp(BattleActionStruct* btlAction);
void BtlAction_InitStatePacket(BattleActionStruct* btlAction);
void BtlAction_UpdateStatePacket(BattleActionStruct* btlAction);
void BtlAction_InitStateEnd(BattleActionStruct* btlAction);
void BtlAction_UpdateStateEnd(BattleActionStruct* btlAction);
void BtlAction_InitStateEndHome(BattleActionStruct* btlAction);
void BtlAction_UpdateStateEndHome(BattleActionStruct* btlAction);
void BtlAction_InitStateDead(BattleActionStruct* btlAction);
void BtlAction_UpdateStateDead(BattleActionStruct* btlAction);
void BtlAction_InitStateExit(BattleActionStruct* btlAction);
void BtlAction_UpdateStateExit(BattleActionStruct* btlAction);
void BtlAction_InitStateTest(BattleActionStruct* btlAction);
void BtlAction_UpdateStateTest(BattleActionStruct* btlAction);

typedef struct
{
    void (*BtlAction_InitState)(BattleActionStruct* btlAction);
    void (*BtlAction_UpdateState)(BattleActionStruct* btlAction);
    const char* name;
} BattleActionStateEntry;

// 00693410
static BattleActionStateEntry gActionStateTable[] = 
{
    {BtlAction_InitStateNon, BtlAction_UpdateStateNon, "NON"},
    {BtlAction_InitStateStandBy, BtlAction_UpdateStateStandBy, "STANDBY"},
    {BtlAction_InitStateStart, BtlAction_UpdateStateStart, "START"},
    {BtlAction_InitStateStartHome, BtlAction_UpdateStateStartHome, "START HOME"},
    {BtlAction_InitStateChangeFormation, BtlAction_UpdateStateChangeFormation, "CHANGE FORMATION"},
    {BtlAction_InitStateCommand, BtlAction_UpdateStateCommand, "COMMAND"},
    {BtlAction_InitStateTarget, BtlAction_UpdateStateTarget, "TARGET"},
    {BtlAction_InitStateAnalyze, BtlAction_UpdateStateAnalyze, "ANALYZE"},
    {BtlAction_InitStateAI, BtlAction_UpdateStateAI, "AI"},
    {BtlAction_InitStateAuto, BtlAction_UpdateStateAuto, "AUTO"},
    {BtlAction_InitStateSupport, BtlAction_UpdateStateSupport, "SUPPORT"},
    {BtlAction_InitStateBad, BtlAction_UpdateStateBad, "BAD"},
    {BtlAction_InitStateReady, BtlAction_UpdateStateReady, "READY"},
    {BtlAction_InitStateMoveTarget, BtlAction_UpdateStateMoveTarget, "MOVE TARGET"},
    {BtlAction_InitStateMoveHome, BtlAction_UpdateStateMoveHome, "MOVE HOME"},
    {BtlAction_InitStateAttack, BtlAction_UpdateStateAttack, "ATTACK"},
    {BtlAction_InitStateSkill, BtlAction_UpdateStateSkill, "SKILL"},
    {BtlAction_InitStateReinforce, BtlAction_UpdateStateReinforce, "REINFORCE"},
    {BtlAction_InitStateSummon, BtlAction_UpdateStateSummon, "SUMMON"},
    {BtlAction_InitStateAssist, BtlAction_UpdateStateAssist, "ASSIST"},
    {BtlAction_InitStateEvent, BtlAction_UpdateStateEvent, "EVENT"},
    {BtlAction_InitStateError, BtlAction_UpdateStateError, "ERROR"},
    {BtlAction_InitStateEndure, BtlAction_UpdateStateEndure, "ENDURE"},
    {BtlAction_InitStateWait, BtlAction_UpdateStateWait, "WAIT"},
    {BtlAction_InitStatePersona, BtlAction_UpdateStatePersona, "PERSONA"},
    {BtlAction_InitStateBadDamage, BtlAction_UpdateStateBadDamage, "BAD DAMAGE"},
    {BtlAction_InitStateEscapeMes, BtlAction_UpdateStateEscapeMes, "ESCAPE MES"},
    {BtlAction_InitStateEscape, BtlAction_UpdateStateEscape, "ESCAPE"},
    {BtlAction_InitStateRoundUpMes, BtlAction_UpdateStateRoundUpMes, "ROUNDUP MES"},
    {BtlAction_InitStateRoundUp, BtlAction_UpdateStateRoundUp, "ROUNDUP"},
    {BtlAction_InitStatePacket, BtlAction_UpdateStatePacket, "PACKET"},
    {BtlAction_InitStateEnd, BtlAction_UpdateStateEnd, "END"},
    {BtlAction_InitStateEndHome, BtlAction_UpdateStateEndHome, "END HOME"},
    {BtlAction_InitStateDead, BtlAction_UpdateStateDead, "DEAD"},
    {BtlAction_InitStateExit, BtlAction_UpdateStateExit, "EXIT"},
    {BtlAction_InitStateTest, BtlAction_UpdateStateTest, "TEST"}
};

// FUN_00289860
u8 BtlAction_CheckPlayWeaponIdleAnim(BattleActionStruct* btlAction)
{
    // TODO

    if (btlAction->idleWeaponAnimTimer <= 0)
    {

    }
    if (btlAction->idleWeaponAnimTimer == 0)
    {

    }

    btlAction->idleWeaponAnimTimer--;
    return false;
}

// FUN_0028a990
void BtlAction_InitStateNon(BattleActionStruct* btlAction)
{
    // nothing
}
// FUN_0028a9a0
void BtlAction_UpdateStateNon(BattleActionStruct* btlAction)
{
    // nothing
}

// FUN_0028a9b0
void BtlAction_InitStateStandBy(BattleActionStruct* btlAction)
{
    // nothing
}
// FUN_0028a9c0
void BtlAction_UpdateStateStandBy(BattleActionStruct* btlAction)
{
    // TODO
}

// FUN_0028aa20
void BtlAction_InitStateStart(BattleActionStruct* btlAction)
{
    // TODO
}
// FUN_0028b230
void BtlAction_UpdateStateStart(BattleActionStruct* btlAction)
{
    // TODO
}

// FUN_0028b800
void BtlAction_InitStateStartHome(BattleActionStruct* btlAction)
{
    // TODO
}
// FUN_0028b9c0
void BtlAction_UpdateStateStartHome(BattleActionStruct* btlAction)
{
    // TODO
}

// FUN_0028ba50
void BtlAction_InitStateChangeFormation(BattleActionStruct* btlAction)
{
    // TODO
}
// FUN_0028bca0
void BtlAction_UpdateStateChangeFormation(BattleActionStruct* btlAction)
{
    // TODO
}

// FUN_0028bd10
void BtlAction_InitStateCommand(BattleActionStruct* btlAction)
{
    // TODO
}
// FUN_0028bf80
void BtlAction_UpdateStateCommand(BattleActionStruct* btlAction)
{
    // TODO
}

// FUN_0028c310
void BtlAction_InitStateTarget(BattleActionStruct* btlAction)
{
    // TODO
}
// FUN_0028c590
void BtlAction_UpdateStateTarget(BattleActionStruct* btlAction)
{
    // TODO
}

// FUN_0028c9f0
void BtlAction_InitStateAnalyze(BattleActionStruct* btlAction)
{
    // TODO
}
// FUN_0028ca00
void BtlAction_UpdateStateAnalyze(BattleActionStruct* btlAction)
{
    // TODO
}

// FUN_0028cda0
void BtlAction_InitStateAI(BattleActionStruct* btlAction)
{
    // TODO
}
// FUN_0028ce50
void BtlAction_UpdateStateAI(BattleActionStruct* btlAction)
{
    // TODO
}

// FUN_0028cf20
void BtlAction_InitStateAuto(BattleActionStruct* btlAction)
{
    // TODO
}
// FUN_0028cf80
void BtlAction_UpdateStateAuto(BattleActionStruct* btlAction)
{
    // TODO
}

// FUN_0028d070
void BtlAction_InitStateSupport(BattleActionStruct* btlAction)
{
    // nothing
}
// FUN_0028d080
void BtlAction_UpdateStateSupport(BattleActionStruct* btlAction)
{
    // TODO
}

// FUN_0028d560
void BtlAction_InitStateBad(BattleActionStruct* btlAction)
{
    // TODO
}
// FUN_0028d5a0
void BtlAction_UpdateStateBad(BattleActionStruct* btlAction)
{
    // TODO
}

// FUN_0028dbe0
void BtlAction_InitStateReady(BattleActionStruct* btlAction)
{
    // nothing
}
// FUN_0028dbf0
void BtlAction_UpdateStateReady(BattleActionStruct* btlAction)
{
    // TODO
}

// FUN_0028df00
void BtlAction_InitStateMoveTarget(BattleActionStruct* btlAction)
{
    // TODO
}
// FUN_0028e740
void BtlAction_UpdateStateMoveTarget(BattleActionStruct* btlAction)
{
    // TODO
}

// FUN_0028e7f0
void BtlAction_InitStateMoveHome(BattleActionStruct* btlAction)
{
    // TODO
}
// FUN_0028ea90
void BtlAction_UpdateStateMoveHome(BattleActionStruct* btlAction)
{
    // TODO
}

// FUN_0028eb40
void BtlAction_InitStateAttack(BattleActionStruct* btlAction)
{
    // nothing
}
// FUN_0028eb50
void BtlAction_UpdateStateAttack(BattleActionStruct* btlAction)
{
    // TODO
}

// FUN_00290bd0
void BtlAction_InitStateSkill(BattleActionStruct* btlAction)
{
    // nothing
}
// FUN_00290be0
void BtlAction_UpdateStateSkill(BattleActionStruct* btlAction)
{
    // TODO
}

// FUN_00294d10
void BtlAction_InitStateReinforce(BattleActionStruct* btlAction)
{
    // nothing
}
// FUN_00294d40
void BtlAction_UpdateStateReinforce(BattleActionStruct* btlAction)
{
    // TODO
}

// FUN_00295150
void BtlAction_InitStateSummon(BattleActionStruct* btlAction)
{
    // nothing
}
// FUN_00295160
void BtlAction_UpdateStateSummon(BattleActionStruct* btlAction)
{
    // TODO
}

// FUN_00295a10
void BtlAction_InitStateAssist(BattleActionStruct* btlAction)
{
    // TODO
}
// FUN_00295b20
void BtlAction_UpdateStateAssist(BattleActionStruct* btlAction)
{
    // TODO
}

// FUN_00295b90
void BtlAction_InitStateEvent(BattleActionStruct* btlAction)
{
    // nothing
}
// FUN_00295ba0
void BtlAction_UpdateStateEvent(BattleActionStruct* btlAction)
{
    // TODO
}

// FUN_00295bf0
void BtlAction_InitStateError(BattleActionStruct* btlAction)
{
    // nothing
}
// FUN_00295c00
void BtlAction_UpdateStateError(BattleActionStruct* btlAction)
{
    // TODO
}

// FUN_00295f00
void BtlAction_InitStateEndure(BattleActionStruct* btlAction)
{
    // TODO
}
// FUN_00295fa0
void BtlAction_UpdateStateEndure(BattleActionStruct* btlAction)
{
    // TODO
}

// FUN_00296310
void BtlAction_InitStateWait(BattleActionStruct* btlAction)
{
    // nothing
}
// FUN_00296320
void BtlAction_UpdateStateWait(BattleActionStruct* btlAction)
{
    // TODO
}

// FUN_00297480
void BtlAction_InitStatePersona(BattleActionStruct* btlAction)
{
    // TODO
}
// FUN_002976d0
void BtlAction_UpdateStatePersona(BattleActionStruct* btlAction)
{
    // TODO
}

// FUN_00297750
void BtlAction_InitStateBadDamage(BattleActionStruct* btlAction)
{
    // TODO
}
// FUN_00297760
void BtlAction_UpdateStateBadDamage(BattleActionStruct* btlAction)
{
    // TODO
}

// FUN_002964f0
void BtlAction_InitStateEscapeMes(BattleActionStruct* btlAction)
{
    // TODO
}
// FUN_00296660
void BtlAction_UpdateStateEscapeMes(BattleActionStruct* btlAction)
{
    // TODO
}

// FUN_00296880
void BtlAction_InitStateEscape(BattleActionStruct* btlAction)
{
    // nothing
}
// FUN_00296890
void BtlAction_UpdateStateEscape(BattleActionStruct* btlAction)
{
    // TODO
}

// FUN_00297a60
void BtlAction_InitStateRoundUpMes(BattleActionStruct* btlAction)
{
    // TODO
}
// FUN_00298060
void BtlAction_UpdateStateRoundUpMes(BattleActionStruct* btlAction)
{
    // TODO
}

// FUN_002984e0
void BtlAction_InitStateRoundUp(BattleActionStruct* btlAction)
{
    // TODO
}
// FUN_00298610
void BtlAction_UpdateStateRoundUp(BattleActionStruct* btlAction)
{
    // TODO
}

// FUN_002990f0
void BtlAction_InitStatePacket(BattleActionStruct* btlAction)
{
    // nothing
}
// FUN_00299100
void BtlAction_UpdateStatePacket(BattleActionStruct* btlAction)
{
    // TODO
}

// FUN_00299170
void BtlAction_InitStateEnd(BattleActionStruct* btlAction)
{
    // TODO
}
// FUN_00299270
void BtlAction_UpdateStateEnd(BattleActionStruct* btlAction)
{
    // TODO
}

// FUN_00299520
void BtlAction_InitStateEndHome(BattleActionStruct* btlAction)
{
    // TODO
}
// FUN_00299760
void BtlAction_UpdateStateEndHome(BattleActionStruct* btlAction)
{
    // TODO
}

// FUN_00299800
void BtlAction_InitStateDead(BattleActionStruct* btlAction)
{
    // TODO
}
// FUN_00299990
void BtlAction_UpdateStateDead(BattleActionStruct* btlAction)
{
    // TODO
}

// FUN_00299aa0
void BtlAction_InitStateExit(BattleActionStruct* btlAction)
{
    // TODO
}
// FUN_00299b00
void BtlAction_UpdateStateExit(BattleActionStruct* btlAction)
{
    // TODO
}

// FUN_00299d20
void BtlAction_InitStateTest(BattleActionStruct* btlAction)
{
    // nothing
}
// FUN_00299d30
void BtlAction_UpdateStateTest(BattleActionStruct* btlAction)
{
    BtlAction_SetStateAndExecute(btlAction, BTL_ACTION_STATE_COMMAND);
}

// FUN_00299d60
void BtlAction_SetStateAndExecute(BattleActionStruct* btlAction, u16 btlState)
{
    btlAction->oldState = btlAction->currState;
    btlAction->currState = btlState;
    btlAction->unkTimer = 0;

    gActionStateTable[btlState].BtlAction_InitState(btlAction);
}