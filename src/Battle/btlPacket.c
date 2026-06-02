#include "Battle/btlPacket.h"
#include "Battle/battle.h"

// FUN_0027e390
BtlPacket* btlPacketFindFirstByActionUID(u64 actionUID, u64 mask)
{
    // TODO

    return NULL;
}

// FUN_0027e410
u32 btlPacketGetCount()
{
    Battle* btl;
    u32 total;
    u32 i;
    BtlPacketList* currList;
    BtlPacket* curr;
    
    total = 0;
    i = 0;
    btl = gBtl;
    for (; i < BTLPACKET_TYPE_MAX; i++)
    {
        currList = &btl->packetLists[i];
        curr = currList->head;

        while (curr != NULL)
        {
            total++;

            curr = curr->next;
        }
    }

    return total;
}

// FUN_0027ec10
BtlPacket* btlPacketCreate(u32 id, u32 workDataSize)
{
    // TODO

    return NULL;
}

// FUN_0027ed20
u64 btlPacketRegister(BtlPacket* packet, s32 type)
{
    // TODO

    return 0;
}