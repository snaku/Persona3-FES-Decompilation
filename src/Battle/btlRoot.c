#include "Battle/btlCtx.h"
#include "Battle/btlMain.h"
#include "Battle/btlActor.h"
#include "Battle/btlAction.h"
#include "Battle/btlRoot.h"
#include "rw/rwplcore.h"
#include "datUnit.h"
#include "temporary.h"

// FUN_00299e90
BattleActor* BtlRoot_CreateActor()
{
    BattleActor* btlActor;

    btlActor = RW_MALLOC(sizeof(BattleActor), 0x40000);
    P3FES_Memset(btlActor, 0, sizeof(BattleActor));

    // FUN_002d1570(btlActor + 0x38);

    btlActor->pendingState = BTL_ACTION_STATE_NON;
    btlActor->unk_14 = 8;

    // uVar3 = FUN_0027cb80();

    // 0xFFFFFFE = u32 max - 1
    if (gUnk_007cc530 > 0xFFFFFFE)
    {
        gUnk_007cc530 = 1;
    }

    btlActor->actorId = gUnk_007cc530;
    btlActor->idleWeaponAnimTimer = -1;
    gUnk_007cc530++;

    // uVar1 = FUN_002ffbc0(0x3c);
    // btlActor->unk_36 = uVar1;
    btlActor->next = NULL;
    
    if (gBtlCtx->prevActorCreated == NULL)
    {
        btlActor->prev = NULL;
    }
    else 
    {
        gBtlCtx->prevActorCreated->next = btlActor;
        btlActor->prev = gBtlCtx->prevActorCreated;
    }
    
    gBtlCtx->prevActorCreated = btlActor;

    BtlAction_SetStateAndInit(btlActor, BTL_ACTION_STATE_NON); // was inlined

    return btlActor;
}

// FUN_00299fb0
void BtlRoot_UpdateActors()
{
    BattleActor* currActor = gBtlCtx->prevActorCreated;
    BattleActor* actorToUpdate = currActor;
    u8 canUpdateActor;

    while (actorToUpdate != NULL)
    {
        actorToUpdate = currActor;
        currActor = actorToUpdate->prev;
        canUpdateActor = true;

        if (actorToUpdate->pendingState != BTL_ACTION_STATE_NON &&
            actorToUpdate->pendingStateTimer != 0)
        {
            actorToUpdate->pendingStateTimer--;
            if (actorToUpdate->pendingStateTimer == 0)
            {
                BtlAction_SetStateAndInit(actorToUpdate, actorToUpdate->pendingState); // was inlined
                actorToUpdate->pendingState = BTL_ACTION_STATE_NON;
            }
            else 
            {
                canUpdateActor = false; // do not update/free actor since timer is not finished
            }
        }

        if (canUpdateActor && !(actorToUpdate->unk_1a & (1 << 2)))
        {
            if (!(actorToUpdate->unk_18 & (1 << 0)) &&
                 (actorToUpdate->unk_1a & (1 << 1)))
            {
                if (actorToUpdate->prev != NULL)
                {
                    actorToUpdate->prev->next = actorToUpdate->next;
                }

                if (actorToUpdate->next == NULL)
                {
                    gBtlCtx->prevActorCreated = actorToUpdate->prev;
                }
                else 
                {
                    actorToUpdate->next->prev = actorToUpdate->prev;
                }

                RW_FREE(actorToUpdate);
            }
            else
            {
                gActionStateTable[actorToUpdate->currState].BtlAction_UpdateState(actorToUpdate);
                actorToUpdate->stateTimer += 2;
            }
        }
    }
}

// FUN_0029a140
void BtlRoot_DestroyAllActors()
{
    BattleActor* currActor = gBtlCtx->prevActorCreated;
    BattleActor* prevActor;

    while (currActor != NULL)
    {   
        prevActor = currActor->prev;
        if (prevActor != NULL)
        {
            prevActor->next = currActor->next;
        }

        if (currActor->next == NULL)
        {
            gBtlCtx->prevActorCreated = currActor->prev;
        }
        else
        {
            currActor->next->prev = currActor->prev;
        }

        RW_FREE(currActor);

        currActor = prevActor;
    }
}

// FUN_0029a1d0
BattleActor* BtlRoot_GetActorByActorCore(BattleActorCore* btlActorCore)
{
    BattleActor* btlActor = gBtlCtx->prevActorCreated;

    while (btlActor != NULL)
    {
        if (btlActor->actorCore == btlActorCore)
        {
            return btlActor;
        }

        btlActor = btlActor->prev;
    }

    return NULL;
}

// FUN_0029a210
BattleActor* BtlRoot_GetActorByActorId(u32 actorId)
{
    BattleActor* btlActor = gBtlCtx->prevActorCreated;

    while (btlActor != NULL)
    {
        if (btlActor->actorId == actorId)
        {
            return btlActor;
        }

        btlActor = btlActor->prev;
    }

    return NULL;
}

// FUN_0029ad20
BattleActor* BtlRoot_GetCurrActorPlaying()
{
    BattleActor* currActorPlaying = gBtlCtx->unkBtlActor_284;
    
    if (currActorPlaying == NULL)
    {
        currActorPlaying = gBtlCtx->currActorPlaying;
    }

    return currActorPlaying;
}