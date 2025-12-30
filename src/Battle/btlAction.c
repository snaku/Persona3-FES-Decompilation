#include "Battle/btlActor.h"
#include "Battle/btlAction.h"
#include "datCalc.h"
#include "temporary.h"

#include <stdlib.h>

void BtlAction_InitStateNon(BattleActor* btlActor);
void BtlAction_UpdateStateNon(BattleActor* btlActor);
void BtlAction_InitStateStandBy(BattleActor* btlActor);
void BtlAction_UpdateStateStandBy(BattleActor* btlActor);
void BtlAction_InitStateStart(BattleActor* btlActor);
void BtlAction_UpdateStateStart(BattleActor* btlActor);
void BtlAction_InitStateStartHome(BattleActor* btlActor);
void BtlAction_UpdateStateStartHome(BattleActor* btlActor);
void BtlAction_InitStateChangeFormation(BattleActor* btlActor);
void BtlAction_UpdateStateChangeFormation(BattleActor* btlActor);
void BtlAction_InitStateCommand(BattleActor* btlActor);
void BtlAction_UpdateStateCommand(BattleActor* btlActor);
void BtlAction_InitStateTarget(BattleActor* btlActor);
void BtlAction_UpdateStateTarget(BattleActor* btlActor);
void BtlAction_InitStateAnalyze(BattleActor* btlActor);
void BtlAction_UpdateStateAnalyze(BattleActor* btlActor);
void BtlAction_InitStateAI(BattleActor* btlActor);
void BtlAction_UpdateStateAI(BattleActor* btlActor);
void BtlAction_InitStateAuto(BattleActor* btlActor);
void BtlAction_UpdateStateAuto(BattleActor* btlActor);
void BtlAction_InitStateSupport(BattleActor* btlActor);
void BtlAction_UpdateStateSupport(BattleActor* btlActor);
void BtlAction_InitStateBad(BattleActor* btlActor);
void BtlAction_UpdateStateBad(BattleActor* btlActor);
void BtlAction_InitStateReady(BattleActor* btlActor);
void BtlAction_UpdateStateReady(BattleActor* btlActor);
void BtlAction_InitStateMoveTarget(BattleActor* btlActor);
void BtlAction_UpdateStateMoveTarget(BattleActor* btlActor);
void BtlAction_InitStateMoveHome(BattleActor* btlActor);
void BtlAction_UpdateStateMoveHome(BattleActor* btlActor);
void BtlAction_InitStateAttack(BattleActor* btlActor);
void BtlAction_UpdateStateAttack(BattleActor* btlActor);
void BtlAction_InitStateSkill(BattleActor* btlActor);
void BtlAction_UpdateStateSkill(BattleActor* btlActor);
void BtlAction_InitStateReinforce(BattleActor* btlActor);
void BtlAction_UpdateStateReinforce(BattleActor* btlActor);
void BtlAction_InitStateSummon(BattleActor* btlActor);
void BtlAction_UpdateStateSummon(BattleActor* btlActor);
void BtlAction_InitStateAssist(BattleActor* btlActor);
void BtlAction_UpdateStateAssist(BattleActor* btlActor);
void BtlAction_InitStateEvent(BattleActor* btlActor);
void BtlAction_UpdateStateEvent(BattleActor* btlActor);
void BtlAction_InitStateError(BattleActor* btlActor);
void BtlAction_UpdateStateError(BattleActor* btlActor);
void BtlAction_InitStateEndure(BattleActor* btlActor);
void BtlAction_UpdateStateEndure(BattleActor* btlActor);
void BtlAction_InitStateWait(BattleActor* btlActor);
void BtlAction_UpdateStateWait(BattleActor* btlActor);
void BtlAction_InitStatePersona(BattleActor* btlActor);
void BtlAction_UpdateStatePersona(BattleActor* btlActor);
void BtlAction_InitStateBadDamage(BattleActor* btlActor);
void BtlAction_UpdateStateBadDamage(BattleActor* btlActor);
void BtlAction_InitStateEscapeMes(BattleActor* btlActor);
void BtlAction_UpdateStateEscapeMes(BattleActor* btlActor);
void BtlAction_InitStateEscape(BattleActor* btlActor);
void BtlAction_UpdateStateEscape(BattleActor* btlActor);
void BtlAction_InitStateRoundUpMes(BattleActor* btlActor);
void BtlAction_UpdateStateRoundUpMes(BattleActor* btlActor);
void BtlAction_InitStateRoundUp(BattleActor* btlActor);
void BtlAction_UpdateStateRoundUp(BattleActor* btlActor);
void BtlAction_InitStatePacket(BattleActor* btlActor);
void BtlAction_UpdateStatePacket(BattleActor* btlActor);
void BtlAction_InitStateEnd(BattleActor* btlActor);
void BtlAction_UpdateStateEnd(BattleActor* btlActor);
void BtlAction_InitStateEndHome(BattleActor* btlActor);
void BtlAction_UpdateStateEndHome(BattleActor* btlActor);
void BtlAction_InitStateDead(BattleActor* btlActor);
void BtlAction_UpdateStateDead(BattleActor* btlActor);
void BtlAction_InitStateExit(BattleActor* btlActor);
void BtlAction_UpdateStateExit(BattleActor* btlActor);
void BtlAction_InitStateTest(BattleActor* btlActor);
void BtlAction_UpdateStateTest(BattleActor* btlActor);

// 007cc530
u32 gUnk_007cc530 = 0;

// 00693410
BattleActionStateEntry gActionStateTable[] = 
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
u8 BtlAction_CheckPlayWeaponIdleAnim(BattleActor* btlActor)
{
    // TODO

    if (btlActor->idleWeaponAnimTimer <= 0)
    {

    }
    if (btlActor->idleWeaponAnimTimer == 0)
    {

    }

    btlActor->idleWeaponAnimTimer--;
    return false;
}

// FUN_0028a990
void BtlAction_InitStateNon(BattleActor* btlActor)
{
    // nothing
}
// FUN_0028a9a0
void BtlAction_UpdateStateNon(BattleActor* btlActor)
{
    // nothing
}

// FUN_0028a9b0
void BtlAction_InitStateStandBy(BattleActor* btlActor)
{
    // nothing
}
// FUN_0028a9c0
void BtlAction_UpdateStateStandBy(BattleActor* btlActor)
{
    // TODO
}

// FUN_0028aa20
void BtlAction_InitStateStart(BattleActor* btlActor)
{
    // TODO
}
// FUN_0028b230
void BtlAction_UpdateStateStart(BattleActor* btlActor)
{
    // TODO
}

// FUN_0028b800
void BtlAction_InitStateStartHome(BattleActor* btlActor)
{
    // TODO
}
// FUN_0028b9c0
void BtlAction_UpdateStateStartHome(BattleActor* btlActor)
{
    // TODO
}

// FUN_0028ba50
void BtlAction_InitStateChangeFormation(BattleActor* btlActor)
{
    // TODO
}
// FUN_0028bca0
void BtlAction_UpdateStateChangeFormation(BattleActor* btlActor)
{
    // TODO
}

// FUN_0028bd10
void BtlAction_InitStateCommand(BattleActor* btlActor)
{
    // TODO
}
// FUN_0028bf80
void BtlAction_UpdateStateCommand(BattleActor* btlActor)
{
    // TODO
}

// FUN_0028c310
void BtlAction_InitStateTarget(BattleActor* btlActor)
{
    // TODO
}
// FUN_0028c590
void BtlAction_UpdateStateTarget(BattleActor* btlActor)
{
    // TODO
}

// FUN_0028c9f0
void BtlAction_InitStateAnalyze(BattleActor* btlActor)
{
    // TODO
}
// FUN_0028ca00
void BtlAction_UpdateStateAnalyze(BattleActor* btlActor)
{
    // TODO
}

// FUN_0028cda0
void BtlAction_InitStateAI(BattleActor* btlActor)
{
    // TODO
}
// FUN_0028ce50
void BtlAction_UpdateStateAI(BattleActor* btlActor)
{
    // TODO
}

// FUN_0028cf20
void BtlAction_InitStateAuto(BattleActor* btlActor)
{
    // TODO
}
// FUN_0028cf80
void BtlAction_UpdateStateAuto(BattleActor* btlActor)
{
    // TODO
}

// FUN_0028d070
void BtlAction_InitStateSupport(BattleActor* btlActor)
{
    // nothing
}
// FUN_0028d080
void BtlAction_UpdateStateSupport(BattleActor* btlActor)
{
    // TODO
}

// FUN_0028d560
void BtlAction_InitStateBad(BattleActor* btlActor)
{
    // TODO
}
// FUN_0028d5a0
void BtlAction_UpdateStateBad(BattleActor* btlActor)
{
    // TODO
}

// FUN_0028dbe0
void BtlAction_InitStateReady(BattleActor* btlActor)
{
    // nothing
}
// FUN_0028dbf0
void BtlAction_UpdateStateReady(BattleActor* btlActor)
{
    // TODO
}

// FUN_0028df00
void BtlAction_InitStateMoveTarget(BattleActor* btlActor)
{
    // TODO
}
// FUN_0028e740
void BtlAction_UpdateStateMoveTarget(BattleActor* btlActor)
{
    // TODO
}

// FUN_0028e7f0
void BtlAction_InitStateMoveHome(BattleActor* btlActor)
{
    // TODO
}
// FUN_0028ea90
void BtlAction_UpdateStateMoveHome(BattleActor* btlActor)
{
    // TODO
}

// FUN_0028eb40
void BtlAction_InitStateAttack(BattleActor* btlActor)
{
    // nothing
}
// FUN_0028eb50
void BtlAction_UpdateStateAttack(BattleActor* btlActor)
{
    // TODO
}

// FUN_00290bd0
void BtlAction_InitStateSkill(BattleActor* btlActor)
{
    // nothing
}
// FUN_00290be0
void BtlAction_UpdateStateSkill(BattleActor* btlActor)
{
    // TODO
}

// FUN_00294d10
void BtlAction_InitStateReinforce(BattleActor* btlActor)
{
    // nothing
}
// FUN_00294d40
void BtlAction_UpdateStateReinforce(BattleActor* btlActor)
{
    // TODO
}

// FUN_00295150
void BtlAction_InitStateSummon(BattleActor* btlActor)
{
    // nothing
}
// FUN_00295160
void BtlAction_UpdateStateSummon(BattleActor* btlActor)
{
    // TODO
}

// FUN_00295a10
void BtlAction_InitStateAssist(BattleActor* btlActor)
{
    // TODO
}
// FUN_00295b20
void BtlAction_UpdateStateAssist(BattleActor* btlActor)
{
    // TODO
}

// FUN_00295b90
void BtlAction_InitStateEvent(BattleActor* btlActor)
{
    // nothing
}
// FUN_00295ba0
void BtlAction_UpdateStateEvent(BattleActor* btlActor)
{
    // TODO
}

// FUN_00295bf0
void BtlAction_InitStateError(BattleActor* btlActor)
{
    // nothing
}
// FUN_00295c00
void BtlAction_UpdateStateError(BattleActor* btlActor)
{
    // TODO
}

// FUN_00295f00
void BtlAction_InitStateEndure(BattleActor* btlActor)
{
    // TODO
}
// FUN_00295fa0
void BtlAction_UpdateStateEndure(BattleActor* btlActor)
{
    // TODO
}

// FUN_00296310
void BtlAction_InitStateWait(BattleActor* btlActor)
{
    // nothing
}
// FUN_00296320
void BtlAction_UpdateStateWait(BattleActor* btlActor)
{
    // TODO
}

// FUN_00297480
void BtlAction_InitStatePersona(BattleActor* btlActor)
{
    // TODO
}
// FUN_002976d0
void BtlAction_UpdateStatePersona(BattleActor* btlActor)
{
    // TODO
}

// FUN_00297750
void BtlAction_InitStateBadDamage(BattleActor* btlActor)
{
    // TODO
}
// FUN_00297760
void BtlAction_UpdateStateBadDamage(BattleActor* btlActor)
{
    // TODO
}

// FUN_002964f0
void BtlAction_InitStateEscapeMes(BattleActor* btlActor)
{
    // TODO
}
// FUN_00296660
void BtlAction_UpdateStateEscapeMes(BattleActor* btlActor)
{
    // TODO
}

// FUN_00296880
void BtlAction_InitStateEscape(BattleActor* btlActor)
{
    // nothing
}
// FUN_00296890
void BtlAction_UpdateStateEscape(BattleActor* btlActor)
{
    // TODO
}

// FUN_00297a60
void BtlAction_InitStateRoundUpMes(BattleActor* btlActor)
{
    // TODO
}
// FUN_00298060
void BtlAction_UpdateStateRoundUpMes(BattleActor* btlActor)
{
    // TODO
}

// FUN_002984e0
void BtlAction_InitStateRoundUp(BattleActor* btlActor)
{
    // TODO
}
// FUN_00298610
void BtlAction_UpdateStateRoundUp(BattleActor* btlActor)
{
    // TODO
}

// FUN_002990f0
void BtlAction_InitStatePacket(BattleActor* btlActor)
{
    // nothing
}
// FUN_00299100
void BtlAction_UpdateStatePacket(BattleActor* btlActor)
{
    // TODO
}

// FUN_00299170
void BtlAction_InitStateEnd(BattleActor* btlActor)
{
    // TODO
}
// FUN_00299270
void BtlAction_UpdateStateEnd(BattleActor* btlActor)
{
    // TODO
}

// FUN_00299520
void BtlAction_InitStateEndHome(BattleActor* btlActor)
{
    // TODO
}
// FUN_00299760
void BtlAction_UpdateStateEndHome(BattleActor* btlActor)
{
    // TODO
}

// FUN_00299800
void BtlAction_InitStateDead(BattleActor* btlActor)
{
    // TODO
}
// FUN_00299990
void BtlAction_UpdateStateDead(BattleActor* btlActor)
{
    // TODO
}

// FUN_00299aa0
void BtlAction_InitStateExit(BattleActor* btlActor)
{
    // TODO
}
// FUN_00299b00
void BtlAction_UpdateStateExit(BattleActor* btlActor)
{
    // TODO
}

// FUN_00299d20
void BtlAction_InitStateTest(BattleActor* btlActor)
{
    // nothing
}
// FUN_00299d30
void BtlAction_UpdateStateTest(BattleActor* btlActor)
{
    BtlAction_SetStateAndInit(btlActor, BTL_ACTION_STATE_COMMAND);
}

// FUN_00299d60
void BtlAction_SetStateAndInit(BattleActor* btlActor, u16 btlState)
{
    btlActor->oldState = btlActor->currState;
    btlActor->currState = btlState;
    btlActor->unkTimer = 0;

    gActionStateTable[btlState].BtlAction_InitState(btlActor);
}

// 01604130