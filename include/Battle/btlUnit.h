#ifndef BTLUNIT_H
#define BTLUNIT_H

#include "Utils.h"
#include "Battle/btlPacket.h"
#include "rw/rtquat.h"

#define BTLUNIT_FLAG2_DEAD   (1 << 0) // 0x01
#define BTLUNIT_FLAG2_UNK08  (1 << 3) // 0x08
#define BTLUNIT_FLAG2_ENDURE (1 << 4) // 0x10
#define BTLUNIT_FLAG2_UNK40  (1 << 6) // 0x40

#define BTLUNIT_LOOKATDEACTIVATE_FLAG_ALLPLAYER (1 << 0) // 0x01
#define BTLUNIT_LOOKATDEACTIVATE_FLAG_ALLENEMY  (1 << 1) // 0x02

typedef struct DatUnit DatUnit;
typedef struct Model Model;
typedef struct BtlPacket BtlPacket;

// TODO
typedef enum
{
    BTLUNIT_PACKET_ANIM = BTLPACKET_MAKE_ID(BTLPACKET_MODULE_UNIT, 0),
    BTLUNIT_PACKET_MOVE = BTLPACKET_MAKE_ID(BTLPACKET_MODULE_UNIT, 10),
    BTLUNIT_PACKET_MOVETOUNIT = BTLPACKET_MAKE_ID(BTLPACKET_MODULE_UNIT, 11),
    BTLUNIT_PACKET_ROTATE = BTLPACKET_MAKE_ID(BTLPACKET_MODULE_UNIT, 13),
    BTLUNIT_PACKET_LOOKAT = BTLPACKET_MAKE_ID(BTLPACKET_MODULE_UNIT, 23),
    BTLUNIT_PACKET_LOOKATUNIT = BTLPACKET_MAKE_ID(BTLPACKET_MODULE_UNIT, 24),
    BTLUNIT_PACKET_LOOKATDEACTIVATE = BTLPACKET_MAKE_ID(BTLPACKET_MODULE_UNIT, 25)
} BtlUnitPacket;

typedef struct BtlUnit BtlUnit;

// 2616 bytes
struct BtlUnit
{
    u32 flags;             // 0x00
    RwV3d pos1;            // 0x04
    RwV3d pos2;            // 0x10
    RtQuat rot;            // 0x1c
    u8 unkData1[0x6c];
    u32 unk_98;            // 0x98
    u32 flags2;            // 0x9c. Temp name
    u16 packetCount;       // 0xa0
    u8 genus;              // 0xa2. See enum 'UnitGenus'
    u16 charId;            // 0xa4
    u32 id;                // 0xa8
    s32 unk_ac;            // 0xac
    u16 lookAtMode;        // 0xb0
    u32 lookAtTargetId;    // 0xb4
    RwV3d lookAtTargetPos; // 0xb8
    u8 unkData2[0x92e];
    u16 resTypeId;         // 0x9f2
    Model* mdl;            // 0x9f4
    u8 unkData3[0x08];
    BtlUnit* personaUnit;  // 0xa00
    u8 unkData4[0x28];
    DatUnit* datUnit;      // 0xa2c
    BtlUnit* prev;         // 0xa30
    BtlUnit* next;         // 0xa34
};

// TODO
typedef enum
{
    BTLUNIT_ANIM_DODGE = -4,
    BTLUNIT_ANIM_RESNULLIFIED = -2,
    BTLUNIT_ANIM_IDLEWEAPON = 16,

    BTLUNIT_ANIM_MAX = 26
} BtlUnitAnim;

// TODO
typedef enum
{
    BTLUNIT_ANIM_MODE_ONCE,
    BTLUNIT_ANIM_MODE_LOOP
} BtlUnitAnimMode;

// 16 bytes
typedef struct BtlUnitPacketAnim
{
    BtlUnit* unit;       // 0x00
    s16 id;              // 0x04. See enum 'BtlUnitAnim'
    u16 blendFrameCount; // 0x06
    f32 speed;           // 0x08
    u16 mode;            // 0x0c. See enum 'BtlUnitAnimMode'
} BtlUnitPacketAnim;

// 36 bytes
typedef struct BtlUnitPacketMove
{
    BtlUnit* unit;    // 0x00
    RwV3d targetPos;  // 0x04 
    u32 flags;        // 0x10
    u16 state;        // 0x14
    u8 unkData[0x06];
    f32 unk_1c;       // 0x1c
    f32 speed;        // 0x20
} BtlUnitPacketMove;

// 40 bytes
typedef struct BtlUnitPacketMoveToUnit
{
    BtlUnitPacketMove move; // 0x00
    BtlUnit* targetUnit;    // 0x24
} BtlUnitPacketMoveToUnit;

// 24 bytes
typedef struct BtlUnitPacketRotate
{
    BtlUnit* unit; // 0x00
    RwV3d rot;     // 0x04
    u32 flags;     // 0x10
    s32 unk_14;    // 0x14
} BtlUnitPacketRotate;

// 20 bytes
typedef struct BtlUnitPacketLookAt
{
    BtlUnit* unit;   // 0x00
    RwV3d targetPos; // 0x04
    u16 flags;       // 0x10
} BtlUnitPacketLookAt;

// 12 bytes
typedef struct BtlUnitPacketLookAtUnit
{
    BtlUnit* unit;       // 0x00
    BtlUnit* targetUnit; // 0x04
    u16 flags;           // 0x08
} BtlUnitPacketLookAtUnit;

// 8 bytes
typedef struct BtlUnitPacketLookAtDeactivate
{
    BtlUnit* unit; // 0x00
    u16 flags;     // 0x04
} BtlUnitPacketLookAtDeactivate;

extern RwV3d gUnk_00957188;

u32 btlUnit00282c60(BtlUnit* unit);
void btlUnitAnimate(BtlUnit* unit, s16 id, u16 blendFrameCount, f32 speed, u32 mode);
s16 btlUnitGetAnimFrame(BtlUnit* unit);
void btlUnitInitFromCharId(BtlUnit* unit, u16 id);
void btlUnitInitPersona(BtlUnit* unit, u16 personaId);
BtlUnit* btlUnitFindFromId(u16 id);

BtlPacket* btlUnitCreateAnimPacket(BtlUnit* unit, u16 id, u16 blendFrameCount, f32 speed, u16 mode);
BtlPacket* btlUnitCreateMovePacket(BtlUnit* unit, const RwV3d* targetPos, f32 speed, u32 flags);
BtlPacket* btlUnitCreateRotatePacket(BtlUnit* unit, const RwV3d* rot, u32 flags);
BtlPacket* btlUnitCreateLookAtPacket(BtlUnit* unit, const RwV3d* targetPos, u16 flags);
BtlPacket* btlUnitCreateLookAtUnitPacket(BtlUnit* unit, BtlUnit* targetUnit, u16 flags);
BtlPacket* btlUnitCreateLookAtDeactivatePacket(BtlUnit* unit, u16 flags);

#endif