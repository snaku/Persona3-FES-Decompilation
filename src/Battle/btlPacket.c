#include "Battle/btlPacket.h"
#include "Battle/battle.h"

// FUN_0027e390
BtlPacket* btlPacketFindFirstByActionUID(u64 actionUID, u64 mask)
{
    Battle* btl;
    u32 i;
    BtlPacketList* currList;
    BtlPacket* curr;

    i = 0;
    btl = gBtl;
    for (; i < BTLPACKET_TYPE_MAX; i++)
    {
        currList = &btl->packetLists[i];
        curr = currList->head;

        while (curr != NULL)
        {
            if (actionUID == (curr->actionUID & mask) &&
                curr->unk_47 & (1 << 5))
            {
                return curr;
            }

            curr = curr->next;
        }
    }

    return NULL;
}

// FUN_0027e410
u32 btlPacketCount()
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

// FUN_0027e470
u32 btlPacketCountById(u16 id)
{
    Battle* btl;
    BtlPacketList* currList;
    BtlPacket* curr;
    u32 total;
    u32 i;
    u32 _id;
    
    total = 0;
    i = 0;
    btl = gBtl;
    _id = id;
    for (; i < BTLPACKET_TYPE_MAX; i++)
    {
        currList = &btl->packetLists[i];
        curr = currList->head;

        while (curr != NULL)
        {
            if (curr->id == _id)
            {
                total++;
            }

            curr = curr->next;
        }
    }

    return total;
}

// FUN_0027e4d0
void btlPacket0027e4d0()
{
    // TODO
}

// FUN_0027ec10
BtlPacket* btlPacketCreate(u32 id, u32 workDataSize)
{
    // TODO

    return NULL;
}

// FUN_0027ed20
u64 btlPacketRegister(BtlPacket* packet, u8 type)
{
    // TODO

    return 0;
}