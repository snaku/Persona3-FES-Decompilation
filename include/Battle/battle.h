#ifndef BATTLE_H
#define BATTLE_H

#include "Battle/btlMain.h"
#include "Battle/btlOrder.h"
#include "Battle/btlPacket.h"
#include "rw/rwplcore.h"
#include "datUnit.h"

#define BTL_FLAG_ACTIVE      (1 << 0)  // 0x01. Currently in a battle. Destroy 'battle' task if not set
#define BTL_FLAG_UNK8000     (1 << 15) // 0x8000
#define BTL_FLAG_MULTI_ENEMY (1 << 16) // 0x10000. More than one enemy in the battle

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
    s32 unk_00;                   // 0x00
    DatUnitPlayer* partyUnits[4]; // 0x04
    DatUnitEnemy* enmUnits;       // 0x14
    u16 fldMajorId;               // 0x18
    u16 fldMinorId;               // 0x1a
    u8 unkData[0x18];
} BtlStartInfo;

// 3440 bytes
typedef struct Battle
{
    u8 unkData1[0x0c];
    u32 flags;                                     // 0x0c
    u8 unkData2[0x138];
    BtlActionList actionList;                      // 0x148
    BtlUnitList unitLists[UNIT_GENUS_MAX];         // 0x150
    u8 unkData3[0x10];
    BtlPacketList packetLists[BTLPACKET_TYPE_MAX]; // 0x170
    u8 unkData4[0xb4];
    u16 fldMajorId;                                // 0x244
    u16 fldMinorId;                                // 0x246
    BtlOrder order;                                // 0x248
    BtlStateWork stateWork;                        // 0x2b4
    u8 unkData6[0x8e8];
    BtlStartInfo startInfo;                        // 0xba8
    u8 unkData7[0x13c];
    KwlnTask* btlTask;                             // 0xd18
    u8 unkData8[0x10];
    KwlnTask* btlPanelTask;                        // 0xd2c
    u8 unkData9[0x40];
} Battle;

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
u32 btlScrCmd_CALL_BATTLE();
KwlnTask* btlGetTask();
void btl0027d8b0();

#endif