#include "Battle/btlActor.h"
#include "Battle/btlAction.h"
#include "Battle/btlMain.h"
#include "temporary.h"

#include <stdlib.h>

// FUN_00299e90
BattleActor* BtlMain_CreateActor()
{
    BattleActor* btlActor;

    // alloc btlActor:

    // btlActor = (*DAT_00960178)(sizeof(BattleActionStruct), 0x40000);
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

    btlActor->unk_08 = gUnk_007cc530;
    btlActor->idleWeaponAnimTimer = -1;
    gUnk_007cc530++;

    // uVar1 = FUN_002ffbc0(0x3c);
    // btlActor->unk_36 = uVar1;
    btlActor->next = NULL;
    
    if (ctx.btlCtx->prevActorCreated == NULL)
    {
        btlActor->prev = NULL;
    }
    else 
    {
        ctx.btlCtx->prevActorCreated->next = btlActor;
        btlActor->prev = ctx.btlCtx->prevActorCreated;
    }
    
    ctx.btlCtx->prevActorCreated = btlActor;

    BtlAction_SetStateAndInit(btlActor, BTL_ACTION_STATE_NON); // was inlined

    return btlActor;
}

// FUN_00299fb0
void BtlMain_UpdateActors()
{
    BattleActor* currActor = ctx.btlCtx->prevActorCreated;
    BattleActor* actorToUpdate = currActor;
    u8 canUpdateActor;

    while (actorToUpdate != NULL)
    {
        actorToUpdate = currActor;
        currActor = actorToUpdate->prev;
        canUpdateActor = true;

        if (actorToUpdate->pendingState != BTL_ACTION_STATE_NON &&
            actorToUpdate->stateTimer != 0)
        {
            actorToUpdate->stateTimer--;
            if (actorToUpdate->stateTimer == 0)
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
                    ctx.btlCtx->prevActorCreated = actorToUpdate->prev;
                }
                else 
                {
                    actorToUpdate->next->prev = actorToUpdate->prev;
                }

                // !!free!!
                // (*0096017c)(actorToUpdate);
            }
            else
            {
                gActionStateTable[actorToUpdate->currState].BtlAction_UpdateState(actorToUpdate);
                actorToUpdate->unkTimer += 2;
            }
        }
    }
}


// FUN_0029ad20
BattleActor* BtlMain_GetCurrActorPlaying()
{
    BattleActor* currActorPlaying = ctx.btlCtx->unkBtlActor_284;
    
    if (currActorPlaying == NULL)
    {
        currActorPlaying = ctx.btlCtx->currActorPlaying;
    }

    return currActorPlaying;
}