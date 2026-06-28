#ifndef BTLBOSS_H
#define BTLBOSS_H

#include "Utils.h"
#include "Battle/btlPacket.h"

typedef struct BtlCameraStateEntry BtlCameraStateEntry;

typedef enum
{
    BTLBOSS_PACKET_LOADPAK = BTLPACKET_MAKE_ID(BTLPACKET_MODULE_BOSS, 0)
} BtlBossPacket;

const BtlCameraStateEntry* btlBossGetCameraStateEntry(u16 cameraState);

BtlPacket* btlBossCreateLoadPakPacket();

#endif