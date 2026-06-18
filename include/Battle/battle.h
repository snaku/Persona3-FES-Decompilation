#ifndef BATTLE_H
#define BATTLE_H

#include "Battle/btlMain.h"
#include "Battle/btlOrder.h"
#include "Battle/btlPacket.h"
#include "Battle/btlCamera.h"
#include "rw/rwplcore.h"
#include "datUnit.h"

#define BTL_FLAG_ACTIVE      (1 << 0)  // 0x01. Currently in a battle. Destroy 'battle' task if not set
#define BTL_FLAG_UNK40       (1 << 6)  // 0x40
#define BTL_FLAG_UNK8000     (1 << 15) // 0x8000
#define BTL_FLAG_MULTI_ENEMY (1 << 16) // 0x10000. More than one enemy in the battle
#define BTL_FLAG_EXIT        (1 << 27) // 0x8000000

#define BTL_UIDMAX  0x3FFFFFFFFFFFFFFF

#define BTL_MAXACTIONS 12

typedef struct KwlnTask KwlnTask;
typedef struct BtlAction BtlAction;
typedef struct BtlUnit BtlUnit;
typedef struct BtlPacket BtlPacket;

// 8 bytes
typedef struct BtlActionList
{
    BtlAction* head; // 0x00
    BtlAction* tail; // 0x04
} BtlActionList;

// 8 bytes
typedef struct BtlUnitList
{
    BtlUnit* head; // 0x00
    BtlUnit* tail; // 0x04
} BtlUnitList;

// 8 bytes
typedef struct BtlPacketList
{
    BtlPacket* tail; // 0x00
    BtlPacket* head; // 0x04
} BtlPacketList;

// 52 bytes
typedef struct BtlStartInfo
{
    s32 unk_00;               // 0x00
    DatUnitPc* partyUnits[4]; // 0x04
    DatUnitEc* enmUnits;      // 0x14
    u16 fldMajorId;           // 0x18
    u16 fldMinorId;           // 0x1a
    u8 unkData[0x18];
} BtlStartInfo;

// 3440 bytes
typedef struct Battle
{
    u8 unkData1[0x0c];
    u32 flags;                                     // 0x0c
    u8 unkData2[0x10];
    BtlCamera camera;                              // 0x20
    u8 unkData3[0x28];
    BtlActionList actionList;                      // 0x148
    BtlUnitList unitLists[UNIT_GENUS_MAX];         // 0x150
    BtlPacketList packetLists[BTLPACKET_TYPE_MAX]; // 0x170
    u8 unkData4[0xb4];
    u16 fldMajorId;                                // 0x244
    u16 fldMinorId;                                // 0x246
    BtlOrder order;                                // 0x248
    BtlStateWork stateWork;                        // 0x2b4
    u8 unkData5[0x8e5];
    u8 hasNoStartInfo;                             // 0xba5
    BtlStartInfo startInfo;                        // 0xba8
    u8 unkData6[0x13c];
    KwlnTask* btlTask;                             // 0xd18
    u8 unkData7[0x10];
    KwlnTask* btlPanelTask;                        // 0xd2c
    u8 unkData8[0x40];
} Battle;

typedef enum
{
    BTLBATTLE_PACKET_SETFLAGS = BTLPACKET_MAKE_ID(BTLPACKET_MODULE_BATTLE, 2),
    BTLBATTLE_PACKET_REMOVEFLAGS = BTLPACKET_MAKE_ID(BTLPACKET_MODULE_BATTLE, 3)
} BtlBattlePacket;

// 4 bytes
typedef struct BtlBattleFlagPacket
{
    u32 flags; // 0x00
} BtlBattleFlagPacket;

typedef enum
{
    BTLENCOUNT_REAPER = 506
} BtlEncountId;

typedef enum
{
    BTLENCOUNT_BGM_FULLMOON = 2,
    BTLENCOUNT_BGM_STREGA,
    BTLENCOUNT_BGM_NYX,
    BTLENCOUNT_BGM_NYXAVATAR,
    BTLENCOUNT_BGM_TARTARUSBOSS,
    BTLENCOUNT_BGM_SEES,
    BTLENCOUNT_BGM_EREBUS
} BtlEncountBgm;

// 28 bytes
typedef struct BtlEncountTable
{
    u8 unkData1[0x08];
    u16 enmIds[5];     // 0x08
    u16 fldMajorId;    // 0x12
    u16 fldMinorId;    // 0x14
    u16 bgm;           // 0x16. See enum 'BtlEncountBgm'
    u8 unkData2[0x04];
} BtlEncountTable;

extern BtlEncountTable* gEncountTbl;
extern Battle* gBtl;

u64 btlGetUID();

KwlnTask* btlStart(BtlStartInfo* startInfo);
void btlStop();
u32 btlScrCmd_CALL_BATTLE();
u32 btlScrCmd_CHK_HERO_DIED_TARTAROS();
KwlnTask* btlGetTask();
void btl0027d8b0();
BtlPacket* btlCreateSetFlagsPacket(u32 flags);

#endif