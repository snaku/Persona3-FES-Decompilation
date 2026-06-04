#include "Battle/btlUnit.h"
#include "Battle/btlPacket.h"
#include "Battle/battle.h"
#include "Model/mdlManager.h"
#include "datUnit.h"

static u32 sNextId = 1; // 007cc51c

RwV3d gUnk_00957188; // 00957188

BtlPacket* btlUnitCreateDodgeAnimPacket(BtlUnit* unit, s32 unused);
BtlPacket* btlUnit00284900(BtlUnit* unit, s32 param_2);
BtlPacket* btlUnitCreateResNullifiedAnimPacket(BtlUnit* unit, f32 param_2);

// FUN_002813d0
void btlUnitInitMovePacket(void* work)
{
    BtlUnitPacketMove* packet;

    packet = (BtlUnitPacketMove*)work;

    packet->unit->packetCount++;
}

// FUN_002813f0
u32 btlUnitUpdateMovePacket(void* work)
{
    // TODO

    return false;
}

// FUN_002819b0
void btlUnitDestroyMovePacket(void* work)
{
    BtlUnitPacketMove* packet;

    packet = (BtlUnitPacketMove*)work;

    packet->unit->packetCount--;
}

// FUN_002819d0
BtlPacket* btlUnitCreateMovePacket(BtlUnit* unit, const RwV3d* targetPos, f32 speed, u32 flags)
{
    BtlPacket* packet;
    BtlUnitPacketMove* work;

    packet = btlPacketCreate(BTLUNIT_PACKET_MOVE, sizeof(BtlUnitPacketMove));

    packet->initFunc = btlUnitInitMovePacket;
    packet->updateFunc = btlUnitUpdateMovePacket;
    packet->destroyFunc = btlUnitDestroyMovePacket;

    work = (BtlUnitPacketMove*)packet->workData;

    work->unit = unit;
    work->speed = speed;
    work->flags = flags;

    if (targetPos != NULL)
    {
        work->targetPos = *targetPos;
    }
    else
    {
        work->targetPos = gUnk_00957188;
    }

    return packet;
}

// FUN_00281ab0
void btlUnitInitMoveToUnitPacket(void* work)
{
    BtlUnitPacketMoveToUnit* packet;

    packet = (BtlUnitPacketMoveToUnit*)work;

    packet->targetUnit->packetCount++;
}

// FUN_00281ad0
u32 btlUnitUpdateMoveToUnitPacket(void* work)
{
    // TODO

    return false;
}

// FUN_00281ab0
void btlUnitDestroyMoveToUnitPacket(void* work)
{
    BtlUnitPacketMoveToUnit* packet;

    packet = (BtlUnitPacketMoveToUnit*)work;

    packet->targetUnit->packetCount--;
}

// FUN_00281e80
BtlPacket* btlUnitCreateMoveToUnitPacket(BtlUnit* unit, BtlUnit* targetUnit, f32 param_3, f32 speed, u32 flags)
{
    BtlPacket* packet;
    BtlUnitPacketMoveToUnit* work;

    packet = btlPacketCreate(BTLUNIT_PACKET_MOVETOUNIT, sizeof(BtlUnitPacketMoveToUnit));
    
    packet->initFunc = btlUnitInitMoveToUnitPacket;
    packet->updateFunc = btlUnitUpdateMoveToUnitPacket;
    packet->destroyFunc = btlUnitDestroyMoveToUnitPacket;

    work = (BtlUnitPacketMoveToUnit*)packet->workData;

    work->move.unit = unit;
    work->move.unk_1c = param_3;
    work->move.speed = speed;
    work->move.flags = flags;
    work->targetUnit = targetUnit;

    return packet;
}

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
BtlPacket* btlUnitCreateRotatePacket(BtlUnit* unit, const RwV3d* rot, u32 flags)
{
    BtlPacket* packet;
    BtlUnitPacketRotate* work;

    packet = btlPacketCreate(BTLUNIT_PACKET_ROTATE, sizeof(BtlUnitPacketRotate));

    packet->initFunc = btlUnitInitRotatePacket;
    packet->updateFunc = btlUnitUpdateRotatePacket;
    packet->destroyFunc = btlUnitDestroyRotatePacket;

    work = (BtlUnitPacketRotate*)packet->workData;

    work->unit = unit;
    work->flags = flags;

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

// FUN_00282c60
u32 btlUnit00282c60(BtlUnit* unit)
{
    // TODO

    return false;
}

// FUN_00282d40
void btlUnitAnimate(BtlUnit* unit, s16 id, u16 blendFrameCount, f32 speed, u32 mode)
{
    // TODO
}

// FUN_00283ba0
s16 btlUnitGetAnimFrame(BtlUnit* unit)
{
    if (unit->unk_98 & (1 << 1))
    {
        return mdlAnimGetCurrentFrame(unit->mdl, 0);
    }

    return 0;
}

// FUN_00284170
void btlUnitInitAnimPacket(void* work)
{
    BtlUnitPacketAnim* packet;

    packet = (BtlUnitPacketAnim*)work;

    packet->unit->packetCount++;
}

// FUN_00284190
u32 btlUnitUpdateAnimPacket(void* work)
{
    BtlUnitPacketAnim* packet;

    packet = (BtlUnitPacketAnim*)work;

    if (packet->id >= 0 && packet->id < BTLUNIT_ANIM_MAX)
    {
        btlUnitAnimate(packet->unit,
                       packet->id,
                       packet->blendFrameCount,
                       packet->speed,
                       packet->mode);
    }

    return true;
}

// FUN_002841e0
void btlUnitDestroyAnimPacket(void* work)
{
    BtlUnitPacketAnim* packet;

    packet = (BtlUnitPacketAnim*)work;

    packet->unit->packetCount--;
}

// FUN_00284200
BtlPacket* btlUnitCreateAnimPacket(BtlUnit* unit, u16 id, u16 blendFrameCount, f32 speed, u16 mode)
{
    BtlPacket* packet;
    BtlUnitPacketAnim* work;
    s16 _id;

    _id = id;
    switch (_id)
    {
        case BTLUNIT_ANIM_RESNULLIFIED: return btlUnitCreateResNullifiedAnimPacket(unit, 32.0f);
        case -3:                        return btlUnit00284900(unit, 6);
        case BTLUNIT_ANIM_DODGE:        return btlUnitCreateDodgeAnimPacket(unit, 6);  
    }

    packet = btlPacketCreate(BTLUNIT_PACKET_ANIM, sizeof(BtlUnitPacketAnim));

    packet->initFunc = btlUnitInitAnimPacket;
    packet->updateFunc = btlUnitUpdateAnimPacket;
    packet->destroyFunc = btlUnitDestroyAnimPacket;

    work = (BtlUnitPacketAnim*)packet->workData;

    work->unit = unit;

    switch (_id)
    {
        case -5:
            _id = -1;
    }

    work->id = _id;
    work->blendFrameCount = blendFrameCount;
    work->speed = speed;
    work->mode = mode;

    return packet;
}

// FUN_00284200
BtlPacket* btlUnitCreateDodgeAnimPacket(BtlUnit* unit, s32 unused)
{
    // TODO

    return NULL;
}

// FUN_00284900
BtlPacket* btlUnit00284900(BtlUnit* unit, s32 param_2)
{
    // TODOD

    return NULL;
}

// FUN_00284b70
BtlPacket* btlUnitCreateResNullifiedAnimPacket(BtlUnit* unit, f32 param_2)
{
    // TODO

    return NULL;
}

// FUN_002875a0
BtlUnit* btlUnitCreate(u8 genus)
{
    // TODO

    return NULL;
}

// FUN_00288170
void btlUnitInitLookAtPacket(void* work)
{
    BtlUnitPacketLookAt* packet;

    packet = (BtlUnitPacketLookAt*)work;

    if (packet->unit != NULL)
    {
        packet->unit->packetCount++;
    }
}

// FUN_00288190
u32 btlUnitUpdateLookAtPacket(void* work)
{
    // TODO

    return false;
}

// FUN_00288340
void btlUnitDestroyLookAtPacket(void* work)
{
    BtlUnitPacketLookAt* packet;

    packet = (BtlUnitPacketLookAt*)work;

    if (packet->unit != NULL)
    {
        packet->unit->packetCount--;
    }
}

// FUN_00288360
BtlPacket* btlUnitCreateLookAtPacket(BtlUnit* unit, const RwV3d* targetPos, u16 flags)
{
    BtlPacket* packet;
    BtlUnitPacketLookAt* work;

    packet = btlPacketCreate(BTLUNIT_PACKET_LOOKAT, sizeof(BtlUnitPacketLookAt));
    
    packet->initFunc = btlUnitInitLookAtPacket;
    packet->updateFunc = btlUnitUpdateLookAtPacket;
    packet->destroyFunc = btlUnitDestroyLookAtPacket;

    work = (BtlUnitPacketLookAt*)packet->workData;

    work->unit = unit;
    work->flags = flags;
    work->targetPos = *targetPos;

    return packet;
}

// FUN_002889c0
void btlUnitInitFromCharId(BtlUnit* unit, u16 id)
{
    // TODO
}

// FUN_00288f80
void btlUnitInitPersona(BtlUnit* unit, u16 personaId)
{
    if (unit->personaUnit == NULL)
    {
        unit->personaUnit = btlUnitCreate(UNIT_GENUS_PERSONA);
    }

    btlUnitInitFromCharId(unit->personaUnit, personaId);
}

// FUN_00289030
BtlUnit* btlUnitFindFromId(u16 id)
{
    u32 i;
    Battle* btl;
    u32 _id;
    BtlUnitList* list;
    BtlUnit* curr;

    i = 0;
    btl = gBtl;
    _id = id;
    for (; i < UNIT_GENUS_MAX; i++)
    {
        list = &btl->unitLists[i];
        curr = list->tail;
        while (curr != NULL)
        {
            if (curr->id == _id)
            {
                return curr;
            }

            curr = curr->prev;
        }
    }

    return NULL;
}