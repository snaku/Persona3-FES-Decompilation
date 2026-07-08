#include "Battle/btlBoss.h"
#include "Battle/battle.h"
#include "Tohyama/h_cdvd.h"

// FUN_002f7dc0
void btlBoss002f7dc0()
{
    // TODO
}

// FUN_002f8840
const BtlCameraStateEntry* btlBossGetCameraStateEntry(u16 cameraState)
{
    // TODO

    return NULL;
}

// FUN_002f9710
void btlBossInitLoadPakPacket(void* work)
{
    // TODO
}

// FUN_002f9b60
u32 btlBossUpdateLoadPakPacket(void* work)
{
    if (gBtl->bossPakCdvd == NULL)
    {
        return true;
    }

    if (H_Cdvd_IsFileLoaded(gBtl->bossPakCdvd))
    {
        btlBoss002f7dc0();

        return true;
    }

    return false;
}

// FUN_002f9bc0
BtlPacket* btlBossCreateLoadPakPacket()
{
    BtlPacket* packet;

    packet = btlPacketCreate(BTLBOSS_PACKET_LOADPAK, 0);

    packet->unk_47 &= ~(1 << 0);
    packet->initFunc = btlBossInitLoadPakPacket;
    packet->updateFunc = btlBossUpdateLoadPakPacket;

    return packet;
}