#include "Battle/battle.h"
#include "Battle/btlUnit.h"
#include "Battle/btlAction.h"
#include "rw/rwplcore.h"
#include "datUnit.h"
#include "datCalc.h"
#include "temporary.h"

void btlActionInitStateNon(BtlAction* action);
void btlActionUpdateStateNon(BtlAction* action);
void btlActionInitStateStandBy(BtlAction* action);
void btlActionUpdateStateStandBy(BtlAction* action);
void btlActionInitStateStart(BtlAction* action);
void btlActionUpdateStateStart(BtlAction* action);
void btlActionInitStateStartHome(BtlAction* action);
void btlActionUpdateStateStartHome(BtlAction* action);
void btlActionInitStateChangeFormation(BtlAction* action);
void btlActionUpdateStateChangeFormation(BtlAction* action);
void btlActionInitStateCommand(BtlAction* action);
void btlActionUpdateStateCommand(BtlAction* action);
void btlActionInitStateTarget(BtlAction* action);
void btlActionUpdateStateTarget(BtlAction* action);
void btlActionInitStateAnalyze(BtlAction* action);
void btlActionUpdateStateAnalyze(BtlAction* action);
void btlActionInitStateAI(BtlAction* action);
void btlActionUpdateStateAI(BtlAction* action);
void btlActionInitStateAuto(BtlAction* action);
void btlActionUpdateStateAuto(BtlAction* action);
void btlActionInitStateSupport(BtlAction* action);
void btlActionUpdateStateSupport(BtlAction* action);
void btlActionInitStateBad(BtlAction* action);
void btlActionUpdateStateBad(BtlAction* action);
void btlActionInitStateReady(BtlAction* action);
void btlActionUpdateStateReady(BtlAction* action);
void btlActionInitStateMoveTarget(BtlAction* action);
void btlActionUpdateStateMoveTarget(BtlAction* action);
void btlActionInitStateMoveHome(BtlAction* action);
void btlActionUpdateStateMoveHome(BtlAction* action);
void btlActionInitStateAttack(BtlAction* action);
void btlActionUpdateStateAttack(BtlAction* action);
void btlActionInitStateSkill(BtlAction* action);
void btlActionUpdateStateSkill(BtlAction* action);
void btlActionInitStateReinforce(BtlAction* action);
void btlActionUpdateStateReinforce(BtlAction* action);
void btlActionInitStateSummon(BtlAction* action);
void btlActionUpdateStateSummon(BtlAction* action);
void btlActionInitStateAssist(BtlAction* action);
void btlActionUpdateStateAssist(BtlAction* action);
void btlActionInitStateEvent(BtlAction* action);
void btlActionUpdateStateEvent(BtlAction* action);
void btlActionInitStateError(BtlAction* action);
void btlActionUpdateStateError(BtlAction* action);
void btlActionInitStateEndure(BtlAction* action);
void btlActionUpdateStateEndure(BtlAction* action);
void btlActionInitStateWait(BtlAction* action);
void btlActionUpdateStateWait(BtlAction* action);
void btlActionInitStatePersona(BtlAction* action);
void btlActionUpdateStatePersona(BtlAction* action);
void btlActionInitStateBadDamage(BtlAction* action);
void btlActionUpdateStateBadDamage(BtlAction* action);
void btlActionInitStateEscapeMes(BtlAction* action);
void btlActionUpdateStateEscapeMes(BtlAction* action);
void btlActionInitStateEscape(BtlAction* action);
void btlActionUpdateStateEscape(BtlAction* action);
void btlActionInitStateRoundUpMes(BtlAction* action);
void btlActionUpdateStateRoundUpMes(BtlAction* action);
void btlActionInitStateRoundUp(BtlAction* action);
void btlActionUpdateStateRoundUp(BtlAction* action);
void btlActionInitStatePacket(BtlAction* action);
void btlActionUpdateStatePacket(BtlAction* action);
void btlActionInitStateEnd(BtlAction* action);
void btlActionUpdateStateEnd(BtlAction* action);
void btlActionInitStateEndHome(BtlAction* action);
void btlActionUpdateStateEndHome(BtlAction* action);
void btlActionInitStateDead(BtlAction* action);
void btlActionUpdateStateDead(BtlAction* action);
void btlActionInitStateExit(BtlAction* action);
void btlActionUpdateStateExit(BtlAction* action);
void btlActionInitStateTest(BtlAction* action);
void btlActionUpdateStateTest(BtlAction* action);

void btlActionSetStateWithDelay(BtlAction* action, u16 btlState, u16 delay);

// 007cc530
u32 gUnk_007cc530 = 0;

// 00693410
BtlActionStateEntry gActionStateTable[] = 
{
    {btlActionInitStateNon, btlActionUpdateStateNon, "NON"},
    {btlActionInitStateStandBy, btlActionUpdateStateStandBy, "STANDBY"},
    {btlActionInitStateStart, btlActionUpdateStateStart, "START"},
    {btlActionInitStateStartHome, btlActionUpdateStateStartHome, "START HOME"},
    {btlActionInitStateChangeFormation, btlActionUpdateStateChangeFormation, "CHANGE FORMATION"},
    {btlActionInitStateCommand, btlActionUpdateStateCommand, "COMMAND"},
    {btlActionInitStateTarget, btlActionUpdateStateTarget, "TARGET"},
    {btlActionInitStateAnalyze, btlActionUpdateStateAnalyze, "ANALYZE"},
    {btlActionInitStateAI, btlActionUpdateStateAI, "AI"},
    {btlActionInitStateAuto, btlActionUpdateStateAuto, "AUTO"},
    {btlActionInitStateSupport, btlActionUpdateStateSupport, "SUPPORT"},
    {btlActionInitStateBad, btlActionUpdateStateBad, "BAD"},
    {btlActionInitStateReady, btlActionUpdateStateReady, "READY"},
    {btlActionInitStateMoveTarget, btlActionUpdateStateMoveTarget, "MOVE TARGET"},
    {btlActionInitStateMoveHome, btlActionUpdateStateMoveHome, "MOVE HOME"},
    {btlActionInitStateAttack, btlActionUpdateStateAttack, "ATTACK"},
    {btlActionInitStateSkill, btlActionUpdateStateSkill, "SKILL"},
    {btlActionInitStateReinforce, btlActionUpdateStateReinforce, "REINFORCE"},
    {btlActionInitStateSummon, btlActionUpdateStateSummon, "SUMMON"},
    {btlActionInitStateAssist, btlActionUpdateStateAssist, "ASSIST"},
    {btlActionInitStateEvent, btlActionUpdateStateEvent, "EVENT"},
    {btlActionInitStateError, btlActionUpdateStateError, "ERROR"},
    {btlActionInitStateEndure, btlActionUpdateStateEndure, "ENDURE"},
    {btlActionInitStateWait, btlActionUpdateStateWait, "WAIT"},
    {btlActionInitStatePersona, btlActionUpdateStatePersona, "PERSONA"},
    {btlActionInitStateBadDamage, btlActionUpdateStateBadDamage, "BAD DAMAGE"},
    {btlActionInitStateEscapeMes, btlActionUpdateStateEscapeMes, "ESCAPE MES"},
    {btlActionInitStateEscape, btlActionUpdateStateEscape, "ESCAPE"},
    {btlActionInitStateRoundUpMes, btlActionUpdateStateRoundUpMes, "ROUNDUP MES"},
    {btlActionInitStateRoundUp, btlActionUpdateStateRoundUp, "ROUNDUP"},
    {btlActionInitStatePacket, btlActionUpdateStatePacket, "PACKET"},
    {btlActionInitStateEnd, btlActionUpdateStateEnd, "END"},
    {btlActionInitStateEndHome, btlActionUpdateStateEndHome, "END HOME"},
    {btlActionInitStateDead, btlActionUpdateStateDead, "DEAD"},
    {btlActionInitStateExit, btlActionUpdateStateExit, "EXIT"},
    {btlActionInitStateTest, btlActionUpdateStateTest, "TEST"}
};

// FUN_00289860
u8 btlActionCheckPlayWeaponIdleAnim(BtlAction* action)
{
    // TODO

    if (action->idleWeaponAnimTimer <= 0)
    {

    }
    if (action->idleWeaponAnimTimer == 0)
    {

    }

    action->idleWeaponAnimTimer--;
    return false;
}

// FUN_0028a990
void btlActionInitStateNon(BtlAction* action)
{
    // nothing
}
// FUN_0028a9a0
void btlActionUpdateStateNon(BtlAction* action)
{
    // nothing
}

// FUN_0028a9b0
void btlActionInitStateStandBy(BtlAction* action)
{
    // nothing
}
// FUN_0028a9c0
void btlActionUpdateStateStandBy(BtlAction* action)
{
    if ((action->unit->unkFlag_9c & (1 << 4)))
    {
        btlActionSetStateAndInit(action, BTLACTION_STATE_ENDURE);
        return;
    }

    if (action->unit->unkFlag_9c & (1 << 0))
    {
        btlActionSetStateAndInit(action, BTLACTION_STATE_DEAD);
    }
}

// FUN_0028aa20
void btlActionInitStateStart(BtlAction* action)
{
    // TODO
}
// FUN_0028b230
void btlActionUpdateStateStart(BtlAction* action)
{
    // TODO
}

// FUN_0028b800
void btlActionInitStateStartHome(BtlAction* action)
{
    // TODO
}
// FUN_0028b9c0
void btlActionUpdateStateStartHome(BtlAction* action)
{
    // TODO
}

// FUN_0028ba50
void btlActionInitStateChangeFormation(BtlAction* action)
{
    // TODO
}
// FUN_0028bca0
void btlActionUpdateStateChangeFormation(BtlAction* action)
{
    // TODO
}

// FUN_0028bd10
void btlActionInitStateCommand(BtlAction* action)
{
    // TODO
}
// FUN_0028bf80
void btlActionUpdateStateCommand(BtlAction* action)
{
    // TODO
}

// FUN_0028c310
void btlActionInitStateTarget(BtlAction* action)
{
    // TODO
}
// FUN_0028c590
void btlActionUpdateStateTarget(BtlAction* action)
{
    // TODO
}

// FUN_0028c9f0
void btlActionInitStateAnalyze(BtlAction* action)
{
    // TODO
}
// FUN_0028ca00
void btlActionUpdateStateAnalyze(BtlAction* action)
{
    // TODO
}

// FUN_0028cda0
void btlActionInitStateAI(BtlAction* action)
{
    // TODO
}
// FUN_0028ce50
void btlActionUpdateStateAI(BtlAction* action)
{
    // TODO
}

// FUN_0028cf20
void btlActionInitStateAuto(BtlAction* action)
{
    // TODO
}
// FUN_0028cf80
void btlActionUpdateStateAuto(BtlAction* action)
{
    // TODO
}

// FUN_0028d070
void btlActionInitStateSupport(BtlAction* action)
{
    // nothing
}
// FUN_0028d080
void btlActionUpdateStateSupport(BtlAction* action)
{
    // TODO
}

// FUN_0028d560
void btlActionInitStateBad(BtlAction* action)
{
    // TODO
}
// FUN_0028d5a0
void btlActionUpdateStateBad(BtlAction* action)
{
    // TODO
}

// FUN_0028dbe0
void btlActionInitStateReady(BtlAction* action)
{
    // nothing
}
// FUN_0028dbf0
void btlActionUpdateStateReady(BtlAction* action)
{
    // TODO
}

// FUN_0028df00
void btlActionInitStateMoveTarget(BtlAction* action)
{
    // TODO
}
// FUN_0028e740
void btlActionUpdateStateMoveTarget(BtlAction* action)
{
    // TODO
}

// FUN_0028e7f0
void btlActionInitStateMoveHome(BtlAction* action)
{
    // TODO
}
// FUN_0028ea90
void btlActionUpdateStateMoveHome(BtlAction* action)
{
    // TODO
}

// FUN_0028eb40
void btlActionInitStateAttack(BtlAction* action)
{
    // nothing
}
// FUN_0028eb50
void btlActionUpdateStateAttack(BtlAction* action)
{
    // TODO
}

// FUN_00290bd0
void btlActionInitStateSkill(BtlAction* action)
{
    // nothing
}
// FUN_00290be0
void btlActionUpdateStateSkill(BtlAction* action)
{
    // TODO
}

// FUN_00294d10
void btlActionInitStateReinforce(BtlAction* action)
{
    // nothing
}
// FUN_00294d40
void btlActionUpdateStateReinforce(BtlAction* action)
{
    // TODO
}

// FUN_00295150
void btlActionInitStateSummon(BtlAction* action)
{
    // nothing
}
// FUN_00295160
void btlActionUpdateStateSummon(BtlAction* action)
{
    // TODO
}

// FUN_00295a10
void btlActionInitStateAssist(BtlAction* action)
{
    // TODO
}
// FUN_00295b20
void btlActionUpdateStateAssist(BtlAction* action)
{
    // TODO
}

// FUN_00295b90
void btlActionInitStateEvent(BtlAction* action)
{
    // nothing
}
// FUN_00295ba0
void btlActionUpdateStateEvent(BtlAction* action)
{
    // TODO
}

// FUN_00295bf0
void btlActionInitStateError(BtlAction* action)
{
    // nothing
}
// FUN_00295c00
void btlActionUpdateStateError(BtlAction* action)
{
    // TODO
}

// FUN_00295f00
void btlActionInitStateEndure(BtlAction* action)
{
    // TODO
}
// FUN_00295fa0
void btlActionUpdateStateEndure(BtlAction* action)
{
    // TODO
}

// FUN_00296310
void btlActionInitStateWait(BtlAction* action)
{
    // nothing
}
// FUN_00296320
void btlActionUpdateStateWait(BtlAction* action)
{
    // TODO
}

// FUN_00297480
void btlActionInitStatePersona(BtlAction* action)
{
    // TODO
}
// FUN_002976d0
void btlActionUpdateStatePersona(BtlAction* action)
{
    // TODO
}

// FUN_00297750
void btlActionInitStateBadDamage(BtlAction* action)
{
    // TODO
}
// FUN_00297760
void btlActionUpdateStateBadDamage(BtlAction* action)
{
    // TODO
}

// FUN_002964f0
void btlActionInitStateEscapeMes(BtlAction* action)
{
    // TODO
}
// FUN_00296660
void btlActionUpdateStateEscapeMes(BtlAction* action)
{
    // TODO
}

// FUN_00296880
void btlActionInitStateEscape(BtlAction* action)
{
    // nothing
}
// FUN_00296890
void btlActionUpdateStateEscape(BtlAction* action)
{
    // TODO
}

// FUN_00297a60
void btlActionInitStateRoundUpMes(BtlAction* action)
{
    // TODO
}
// FUN_00298060
void btlActionUpdateStateRoundUpMes(BtlAction* action)
{
    // TODO
}

// FUN_002984e0
void btlActionInitStateRoundUp(BtlAction* action)
{
    // TODO
}
// FUN_00298610
void btlActionUpdateStateRoundUp(BtlAction* action)
{
    // TODO
}

// FUN_002990f0
void btlActionInitStatePacket(BtlAction* action)
{
    // nothing
}
// FUN_00299100
void btlActionUpdateStatePacket(BtlAction* action)
{
    // TODO
}

// FUN_00299170
void btlActionInitStateEnd(BtlAction* action)
{
    // TODO
}
// FUN_00299270
void btlActionUpdateStateEnd(BtlAction* action)
{
    // TODO
}

// FUN_00299520
void btlActionInitStateEndHome(BtlAction* action)
{
    // TODO
}
// FUN_00299760
void btlActionUpdateStateEndHome(BtlAction* action)
{
    // TODO
}

// FUN_00299800
void btlActionInitStateDead(BtlAction* action)
{
    // TODO
}
// FUN_00299990
void btlActionUpdateStateDead(BtlAction* action)
{
    // TODO
}

// FUN_00299aa0
void btlActionInitStateExit(BtlAction* action)
{
    // TODO
}
// FUN_00299b00
void btlActionUpdateStateExit(BtlAction* action)
{
    // TODO
}

// FUN_00299d20
void btlActionInitStateTest(BtlAction* action)
{
    // nothing
}
// FUN_00299d30
void btlActionUpdateStateTest(BtlAction* action)
{
    btlActionSetStateAndInit(action, BTLACTION_STATE_COMMAND);
}

// FUN_00299d60
void btlActionSetStateAndInit(BtlAction* action, u16 btlState)
{
    action->oldState = action->currState;
    action->currState = btlState;
    action->stateTimer = 0;

    gActionStateTable[btlState].init(action);
}

// FUN_00299db0. 'delay' = number of frames
void btlActionSetStateWithDelay(BtlAction* action, u16 btlState, u16 delay)
{
    if (delay == 0)
    {
        action->pendingState = BTLACTION_STATE_NON;
        action->pendingStateTimer = 0;

        action->oldState = action->currState;
        action->currState = btlState;
        action->stateTimer = 0;

        gActionStateTable[btlState].init(action);

        return;
    }

    action->pendingState = btlState;
    action->pendingStateTimer = delay;
}

// FUN_00299e90
BtlAction* btlActionCreate()
{
    // WIP

    BtlAction* action;

    action = RwMalloc(sizeof(BtlAction), rwMEMHINTDUR_GLOBAL);
    memset(action, 0, sizeof(BtlAction));

    // FUN_002d1570(action + 0x38);

    action->pendingState = BTLACTION_STATE_NON;
    action->unk_14 = 8;

    // uVar3 = FUN_0027cb80();

    // 0xFFFFFFE = u32 max - 1
    if (gUnk_007cc530 > 0xFFFFFFE)
    {
        gUnk_007cc530 = 1;
    }

    action->id = gUnk_007cc530;
    action->idleWeaponAnimTimer = -1;
    gUnk_007cc530++;

    // uVar1 = FUN_002ffbc0(0x3c);
    // ACTION->unk_36 = uVar1;
    action->next = NULL;
    
    if (gBtl->prevActionCreated == NULL)
    {
        action->prev = NULL;
    }
    else 
    {
        gBtl->prevActionCreated->next = action;
        action->prev = gBtl->prevActionCreated;
    }
    
    gBtl->prevActionCreated = action;

    action->oldState = action->currState;
    action->currState = BTLACTION_STATE_NON;
    action->stateTimer = 0;

    gActionStateTable[BTLACTION_STATE_NON].init(action);

    return action;
}

// FUN_00299fb0
void btlActionUpdate()
{
    BtlAction* currAction;
    BtlAction* actionToUpdate;
    u8 canUpdateAction;

    currAction = gBtl->prevActionCreated;
    actionToUpdate = currAction;
    while (actionToUpdate != NULL)
    {
        actionToUpdate = currAction;
        currAction = actionToUpdate->prev;
        canUpdateAction = true;

        if (actionToUpdate->pendingState != BTLACTION_STATE_NON &&
            actionToUpdate->pendingStateTimer != 0)
        {
            actionToUpdate->pendingStateTimer--;
            if (actionToUpdate->pendingStateTimer == 0)
            {
                actionToUpdate->oldState = actionToUpdate->currState;
                actionToUpdate->currState = actionToUpdate->pendingState;
                actionToUpdate->stateTimer = 0;

                gActionStateTable[actionToUpdate->pendingState].init(actionToUpdate);

                actionToUpdate->pendingState = BTLACTION_STATE_NON;
            }
            else 
            {
                canUpdateAction = false; // do not update/free actor since timer is not finished
            }
        }

        if (canUpdateAction && !(actionToUpdate->unk_1a & (1 << 2)))
        {
            if (!(actionToUpdate->unk_18 & (1 << 0)) &&
                 (actionToUpdate->unk_1a & (1 << 1)))
            {
                if (actionToUpdate->prev != NULL)
                {
                    actionToUpdate->prev->next = actionToUpdate->next;
                }

                if (actionToUpdate->next == NULL)
                {
                    gBtl->prevActionCreated = actionToUpdate->prev;
                }
                else 
                {
                    actionToUpdate->next->prev = actionToUpdate->prev;
                }

                RwFree(actionToUpdate);
            }
            else
            {
                gActionStateTable[actionToUpdate->currState].update(actionToUpdate);
                actionToUpdate->stateTimer += 2;
            }
        }
    }
}

// FUN_0029a140
void btlActionDestroyAll()
{
    BtlAction* currAction;
    BtlAction* prevAction;

    currAction = gBtl->prevActionCreated;
    while (currAction != NULL)
    {   
        prevAction = currAction->prev;
        if (prevAction != NULL)
        {
            prevAction->next = currAction->next;
        }

        if (currAction->next == NULL)
        {
            gBtl->prevActionCreated = currAction->prev;
        }
        else
        {
            currAction->next->prev = currAction->prev;
        }

        RwFree(currAction);

        currAction = prevAction;
    }
}

// FUN_0029a1d0
BtlAction* btlActionFindByUnit(BtlUnit* unit)
{
    BtlAction* action;

    action = gBtl->prevActionCreated;
    while (action != NULL)
    {
        if (action->unit == unit)
        {
            return action;
        }

        action = action->prev;
    }

    return NULL;
}

// FUN_0029a210
BtlAction* btlActionFindById(u32 id)
{
    BtlAction* action;

    action = gBtl->prevActionCreated;
    while (action != NULL)
    {
        if (action->id == id)
        {
            return action;
        }

        action = action->prev;
    }

    return NULL;
}

// FUN_0029ad20
BtlAction* btlActionGetPlaying()
{
    BtlAction* action;

    action = gBtl->unk_284;
    if (action == NULL)
    {
        action = gBtl->currActionPlaying;
    }

    return action;
}