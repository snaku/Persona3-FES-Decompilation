#include "Battle/btlUnit.h"
#include "Battle/btlPacket.h"

static u32 sNextId = 1; // 007cc51c

RwV3d gUnk_00957188; // 00957188

// FUN_00282190
void btlUnitInitRotatePacket(void* work)
{
    BtlUnitPacketRotate* packet;

    packet = (BtlUnitPacketRotate*)work;

    packet->unit->packetCount++;
}

// FUN_002821b0
u32 btlUnitUpdateRotatePacket(void* work)
{
    // TODO

    return false;
}

// FUN_00282290
void btlUnitDestroyRotatePacket(void* work)
{
    BtlUnitPacketRotate* packet;

    packet = (BtlUnitPacketRotate*)work;

    packet->unit->packetCount--;
}

// FUN_002822b0
BtlPacket* btlUnitCreateRotatePacket(BtlUnit* unit, const RwV3d* rot, s32 param_3)
{
    BtlPacket* packet;
    BtlUnitPacketRotate* work;

    packet = btlPacketCreate(BTLUNIT_PACKET_ROTATE, sizeof(BtlUnitPacketRotate));

    packet->initFunc = btlUnitInitRotatePacket;
    packet->updateFunc = btlUnitUpdateRotatePacket;
    packet->destroyFunc = btlUnitDestroyRotatePacket;

    work = (BtlUnitPacketRotate*)packet->workData;

    work->unit = unit;
    work->unk_10 = param_3;

    if (rot != NULL)
    {
        work->rot = *rot;
    }
    else
    {
        work->rot = gUnk_00957188;
    }

    return packet;
}

// FUN_002875a0
BtlUnit* btlUnitCreate(u8 genus)
{
    // TODO

    return NULL;
}