#ifndef BTLSOUND_H
#define BTLSOUND_H

#include "Utils.h"
#include "Battle/btlPacket.h"

#define BTLSOUND_SKILLSE_FLAG_UNK01 (1 << 0) // 0x01

typedef struct HCdvd HCdvd;
typedef struct BtlPacket BtlPacket;

typedef enum
{
    BTLSOUND_PACKET_SKILLSE = BTLPACKET_MAKE_ID(BTLPACKET_MODULE_SOUND, 3)
} BtlSoundPacket;

// 16 bytes
typedef struct BtlSoundPacketSkillSE
{
    u32 timer;   // 0x00
    u16 skillId; // 0x04
    u16 state;   // 0x06
    HCdvd* cdvd; // 0x08
    u16 flags;   // 0x0c
} BtlSoundPacketSkillSE;

void btlSoundPlayBgm();

BtlPacket* btlSoundCreateSkillSEPacket(u16 skillId, u16 flags);

#endif