#include "Battle/battle.h"
#include "Battle/btlAction.h"
#include "Battle/btlMain.h"
#include "Battle/btlOrder.h"
#include "Battle/btlUnit.h"
#include "Battle/btlPacket.h"
#include "Effect/effMisc.h"
#include "datCalc.h"
#include "temporary.h"

#define BTLACTION_IDMAX 0xFFFFFFF

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

// 12 bytes
typedef struct
{
    void (*init)(BtlAction* action);   // 0x00
    void (*update)(BtlAction* action); // 0x04
    const char* name;                  // 0x08
} BtlActionStateEntry;

// 00693410
static const BtlActionStateEntry sActionStateTable[] =
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

static u32 sNextId = 1; // 007cc530

// FUN_00289860
u32 btlActionIdleWeaponAnim(BtlAction* action)
{
    BtlPacket* animPacket;

    if (action->idleWeaponAnimTimer < 0)
    {
        action->idleWeaponAnimTimer = (effMiscRand(NULL) % 240) + 120; // [120;359]
    }

    if (action->idleWeaponAnimTimer == 0)
    {
        if (!btlUnit00282c60(action->unit))
        {
            return false;
        }
        if (datCalcChkBadStatus(action->unit->datUnit, UNIT_BADSTATUS_DOWN))
        {
            return false;
        }
        if (datCalcChkBadStatus(action->unit->datUnit, 0xFFFFF))
        {
            return false;
        }
        if (datCalcIsLowHp(action->unit->datUnit) || datCalcIsDead(action->unit->datUnit, 0))
        {
            return false;
        }

        if (btlUnitGetAnimFrame(action->unit) < 4)
        {
            animPacket = btlUnitCreateAnimPacket(action->unit,
                                                 BTLUNIT_ANIM_IDLEWEAPON,
                                                 4,
                                                 1.0f,
                                                 BTLUNIT_ANIM_MODE_ONCE);
            btlPacketRegister(animPacket, BTLPACKET_TYPE_1);

            action->idleWeaponAnimTimer = -1;
        }

        return true;
    }
    else
    {
        action->idleWeaponAnimTimer--;
    }

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
    BtlUnit* unit;

    unit = action->unit;

    if (unit->flags3 & BTLUNIT_FLAG3_ENDURE)
    {
        btlActionSetState(action, BTLACTION_STATE_ENDURE);
        return;
    }

    if (unit->flags3 & BTLUNIT_FLAG3_DEAD)
    {
        btlActionSetState(action, BTLACTION_STATE_DEAD);
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
    if (!action->evtFunc())
    {
        btlActionSetState(action, action->stateAfterEvt);
    }
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
    if (btlPacketFindFirstByActionUID(action->uid, BTL_UIDMAX) == NULL)
    {
        btlActionSetState(action, BTLACTION_STATE_END);
    }
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
    RwV3d rot;
    BtlPacket* rotPacket;

    if (!btlUnitIsMoving(action->unit))
    {
        if (action->movedAwayFromHome == true)
        {
            btlUnit0027f7c0(action->unit, NULL, NULL, &rot);

            rotPacket = btlUnitCreateRotatePacket(action->unit, &rot, 0);
            rotPacket->actionUID = action->uid;

            btlPacketRegister(rotPacket, BTLPACKET_TYPE_1);
        }

        btlActionSetState(action, BTLACTION_STATE_STANDBY);
    }
}

// FUN_00299800
void btlActionInitStateDead(BtlAction* action)
{
    // TODO
}
// FUN_00299990
void btlActionUpdateStateDead(BtlAction* action)
{
    BtlUnit* unit;

    unit = action->unit;
    switch (unit->genus)
    {
        case UNIT_GENUS_PC:
            if (!datCalcIsDead(unit->datUnit, 0))
            {
                unit->flags3 &= ~BTLUNIT_FLAG3_DEAD;

                btlOrderAddAction(action);
                btlActionSetState(action, BTLACTION_STATE_STANDBY);
            }
            break;

        case UNIT_GENUS_EC:
            if (!(unit->flags3 & BTLUNIT_FLAG3_UNK40))
            {
                btlActionSetState(action, BTLACTION_STATE_EXIT);
            }
            else
            {
                if (!datCalcIsDead(unit->datUnit, 0))
                {
                    unit->flags3 &= ~BTLUNIT_FLAG3_DEAD;

                    btlOrderAddAction(action);
                    btlActionSetState(action, BTLACTION_STATE_STANDBY);
                }
            }
    }
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
    btlActionSetState(action, BTLACTION_STATE_COMMAND);
}

// FUN_00299d60
void btlActionSetState(BtlAction* action, u16 btlState)
{
    action->oldState = action->currState;
    action->currState = btlState;
    action->stateTimer = 0;

    sActionStateTable[btlState].init(action);
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

        sActionStateTable[btlState].init(action);

        return;
    }

    action->pendingState = btlState;
    action->pendingStateTimer = delay;
}

// FUN_00299e70
void btlActionSetUnit(BtlAction* action, BtlUnit* unit)
{
    action->unit = unit;
    action->unk_1a |= (1 << 0);
}

// FUN_00299e90
BtlAction* btlActionCreate()
{
    BtlAction* action;
    u32 id;

    action = RwMalloc(sizeof(BtlAction), rwMEMHINTDUR_GLOBAL);
    memset(action, 0, sizeof(BtlAction));

    btlTargetInit(&action->target);

    action->pendingState = BTLACTION_STATE_NON;
    action->unk_14 = 8;
    action->uid = btlGetUID();

    if (sNextId >= BTLACTION_IDMAX)
    {
        sNextId = 1;
    }

    id = sNextId;
    sNextId++;
    action->id = id;
    action->idleWeaponAnimTimer = -1;
    action->rand = datCalcRand(60);
    action->next = NULL;

    if (gBtl->actionList.tail != NULL)
    {
        gBtl->actionList.tail->next = action;
        action->prev = gBtl->actionList.tail;
    }
    else 
    {
        action->prev = NULL;
    }
    
    gBtl->actionList.tail = action;

    action->oldState = action->currState;
    action->currState = BTLACTION_STATE_NON;
    action->stateTimer = 0;

    sActionStateTable[BTLACTION_STATE_NON].init(action);

    return action;
}

// FUN_00299fb0
void btlActionUpdateAll()
{
    BtlAction* curr;
    BtlAction* prev;
    u32 canUpdateAction;
    u32 currState;
    u32 pendingState;
    const BtlActionStateEntry* stateEntry;

    curr = gBtl->actionList.tail;
    while (curr != NULL)
    {
        prev = curr->prev;
        canUpdateAction = true;

        if (curr->pendingState != BTLACTION_STATE_NON &&
            curr->pendingStateTimer > 0)
        {
            if (--curr->pendingStateTimer == 0)
            {
                currState = curr->currState;
                pendingState = curr->pendingState;
                curr->oldState = currState;
                curr->currState = pendingState;
                curr->stateTimer = 0;

                sActionStateTable[pendingState].init(curr);

                curr->pendingState = BTLACTION_STATE_NON;
            }
            else 
            {
                canUpdateAction = false;
            }
        }

        if (canUpdateAction && !(curr->unk_1a & (1 << 2)))
        {
            if (curr->unk_18 & (1 << 0))
            {
                stateEntry = &sActionStateTable[curr->currState];
                stateEntry->update(curr);

                curr->stateTimer += 2;
            }
            else if (curr->unk_1a & (1 << 1))
            {
                if (curr->prev != NULL)
                {
                    curr->prev->next = curr->next;
                }

                if (curr->next != NULL)
                {
                    curr->next->prev = curr->prev;
                }
                else 
                {
                    gBtl->actionList.tail = curr->prev;
                }

                RwFree(curr);
            }
        }

        curr = prev;
    }
}

// FUN_0029a140
void btlActionDestroyAll()
{
    BtlAction* currAction;
    BtlAction* prevAction;

    currAction = gBtl->actionList.tail;
    while (currAction != NULL)
    {   
        prevAction = currAction->prev;
        if (prevAction != NULL)
        {
            prevAction->next = currAction->next;
        }

        if (currAction->next == NULL)
        {
            gBtl->actionList.tail = currAction->prev;
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

    action = gBtl->actionList.tail;
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

    action = gBtl->actionList.tail;
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