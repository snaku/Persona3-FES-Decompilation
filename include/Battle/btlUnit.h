#ifndef BTLUNIT_H
#define BTLUNIT_H

#include "Utils.h"
#include "Battle/btlPacket.h"
#include "rw/rtquat.h"

#define BTLUNIT_FLAG_FADE (1 << 0) // 0x01

#define BTLUNIT_FLAG2_UPDATE (1 << 1)  // 0x02
#define BTLUNIT_FLAG2_DIRTY  (1 << 2)  // 0x04

#define BTLUNIT_FLAG3_DEAD   (1 << 0) // 0x01
#define BTLUNIT_FLAG3_UNK08  (1 << 3) // 0x08
#define BTLUNIT_FLAG3_ENDURE (1 << 4) // 0x10
#define BTLUNIT_FLAG3_UNK40  (1 << 6) // 0x40
#define BTLUNIT_FLAG3_NOROT  (1 << 13) // 0x2000

#define BTLUNIT_MOVEMENTFLAGS_MOVE   (1 << 0) // 0x01
#define BTLUNIT_MOVEMENTFLAGS_ROTATE (1 << 1) // 0x02

#define BTLUNIT_LOOKAT_FLAG_ALLPLAYER (1 << 0) // 0x01
#define BTLUNIT_LOOKAT_FLAG_ALLENEMY  (1 << 1) // 0x02

#define BTLUNIT_POSROTCOL_FLAG_SETPOS (1 << 0) // 0x01
#define BTLUNIT_POSROTCOL_FLAG_SETROT (1 << 1) // 0x02
#define BTLUNIT_POSROTCOL_FLAG_SETCOL (1 << 2) // 0x04  

typedef struct DatUnit DatUnit;
typedef struct Model Model;
typedef struct BtlPacket BtlPacket;

// TODO
typedef enum
{
    BTLUNIT_COL_MAIN,

    BTLUNIT_COL_MAX = 5
} BtlUnitColor;

typedef enum
{
    BTLUNIT_LOOKAT_MODE_NONE,
    BTLUNIT_LOOKAT_MODE_TARGETPOS,
    BTLUNIT_LOOKAT_MODE_TARGETUNIT
} BtlUnitLookAtMode;

typedef struct BtlUnit BtlUnit;

// 2616 bytes
struct BtlUnit
{
    u16 flags;                    // 0x00. See 'BTLUNIT_FLAG_*'
    RwV3d pos;                    // 0x04
    RwV3d posOffset;              // 0x10
    RtQuat rot;                   // 0x1c
    f32 scale;                    // 0x2c
    RwRGBA cols[BTLUNIT_COL_MAX]; // 0x30
    u8 unkData1[0x3c];
    RwV3d sphereCenter;           // 0x80
    f32 unk_8c;                   // 0x8c
    f32 sphereRadius;             // 0x90
    s32 unk_94;                   // 0x94
    u32 flags2;                   // 0x98. Temp name. See 'BTLUNIT_FLAG2_*'
    u32 flags3;                   // 0x9c. Temp name. See 'BTLUNIT_FLAG3_*'
    u16 packetCount;              // 0xa0
    u8 genus;                     // 0xa2. See enum 'UnitGenus'
    u16 charId;                   // 0xa4
    u32 id;                       // 0xa8
    s32 unk_ac;                   // 0xac
    u16 lookAtMode;               // 0xb0. See enum 'BtlUnitLookAtMode'
    u32 lookAtTargetId;           // 0xb4
    RwV3d lookAtTargetPos;        // 0xb8
    u32 unk_c4;                   // 0xc4
    u16 movementFlags;            // 0xc8. See 'BTLUNIT_MOVEMENTFLAGS_*'
    u8 unkData2[0x06];
    RwV3d targetRot;              // 0xd0
    u8 unkData3[0x0c];
    s32 unk_e8;                   // 0xe8
    u8 unkData5[0x40c];
    s32 unk_4f8;                  // 0x4f8
    u8 unkData6[0x4f6];
    u16 resTypeId;                // 0x9f2
    Model* mdl;                   // 0x9f4
    u8 unkData7[0x08];
    BtlUnit* personaUnit;         // 0xa00
    u8 unkData8[0x28];
    DatUnit* datUnit;             // 0xa2c
    BtlUnit* prev;                // 0xa30
    BtlUnit* next;                // 0xa34
};

// TODO
typedef enum
{
    BTLUNIT_PACKET_ANIM = BTLPACKET_MAKE_ID(BTLPACKET_MODULE_UNIT, 0),
    BTLUNIT_PACKET_MOVE = BTLPACKET_MAKE_ID(BTLPACKET_MODULE_UNIT, 10),
    BTLUNIT_PACKET_MOVETOUNIT = BTLPACKET_MAKE_ID(BTLPACKET_MODULE_UNIT, 11),
    BTLUNIT_PACKET_ROTATE = BTLPACKET_MAKE_ID(BTLPACKET_MODULE_UNIT, 13),
    BTLUNIT_PACKET_ROTATETOWARDUNIT = BTLPACKET_MAKE_ID(BTLPACKET_MODULE_UNIT, 14),
    BTLUNIT_PACKET_LOOKAT = BTLPACKET_MAKE_ID(BTLPACKET_MODULE_UNIT, 23),
    BTLUNIT_PACKET_LOOKATUNIT = BTLPACKET_MAKE_ID(BTLPACKET_MODULE_UNIT, 24),
    BTLUNIT_PACKET_LOOKATDEACTIVATE = BTLPACKET_MAKE_ID(BTLPACKET_MODULE_UNIT, 25),
    BTLUNIT_PACKET_POSROTCOL = BTLPACKET_MAKE_ID(BTLPACKET_MODULE_UNIT, 27)
} BtlUnitPacket;

// TODO
typedef enum
{
    BTLUNIT_ANIM_ENMDODGE = -4,
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
    u32 timer;     // 0x14
} BtlUnitPacketRotate;

// 16 bytes
typedef struct BtlUnitPacketRotateTowardUnit
{
    BtlUnit* unit;       // 0x00
    BtlUnit* targetUnit; // 0x04
    u32 flags;           // 0x08
    u32 timer;           // 0x0c
} BtlUnitPacketRotateTowardUnit;

// 20 bytes
typedef struct BtlUnitPacketLookAt
{
    BtlUnit* unit;   // 0x00
    RwV3d targetPos; // 0x04
    u16 flags;       // 0x10. See 'BTLUNIT_LOOKAT_FLAG_*'
} BtlUnitPacketLookAt;

// 12 bytes
typedef struct BtlUnitPacketLookAtUnit
{
    BtlUnit* unit;       // 0x00
    BtlUnit* targetUnit; // 0x04
    u16 flags;           // 0x08. See 'BTLUNIT_LOOKAT_FLAG_*'
} BtlUnitPacketLookAtUnit;

// 8 bytes
typedef struct BtlUnitPacketLookAtDeactivate
{
    BtlUnit* unit; // 0x00
    u16 flags;     // 0x04. See 'BTLUNIT_LOOKAT_FLAG_*'
} BtlUnitPacketLookAtDeactivate;

// 40 bytes
typedef struct BtlUnitPacketPosRotCol
{
    BtlUnit* unit; // 0x00
    RwV3d pos;     // 0x04
    RtQuat rot;    // 0x10
    RwRGBA col;    // 0x20
    u16 flags;     // 0x24. See 'BTLUNIT_POSROTCOL_FLAG_*'
} BtlUnitPacketPosRotCol;

extern RwV3d gUnk_00957188;

void btlUnitSetPos(BtlUnit* unit, const RwV3d* pos);
void btlUnitSetRot(BtlUnit* unit, const RtQuat* rot);
void btlUnitSetRotFromMat(BtlUnit* unit, const RwMatrix* mat);
void btlUnitSetScale(BtlUnit* unit, f32 scale);
void btlUnitSetColor(BtlUnit* unit, RwRGBA col);
void btlUnitSetFlags(BtlUnit* unit, u16 flags);
void btlUnitClearFlags(BtlUnit* unit, u16 flags);
void btlUnit0027f7c0(BtlUnit* unit, RwV3d* param_2, RwV3d* parm_3, RwV3d* param_4);
void btlUnitGetSphereWorldCenter(BtlUnit* unit, RwV3d* dst);
u32 btlUnitIsMoving(BtlUnit* unit);
void btlUnitStopMoving(BtlUnit* unit);
void btlUnitStopRotating(BtlUnit* unit);
u32 btlUnit00282c60(BtlUnit* unit);
void btlUnitAnimate(BtlUnit* unit, s16 id, u16 blendFrameCount, f32 speed, u32 mode);
s16 btlUnitGetAnimFrame(BtlUnit* unit);
void btlUnitInitFromCharId(BtlUnit* unit, u16 id);
void btlUnitInitPersona(BtlUnit* unit, u16 personaId);
BtlUnit* btlUnitFindFromId(u16 id);

BtlPacket* btlUnitCreateAnimPacket(BtlUnit* unit, u16 id, u16 blendFrameCount, f32 speed, u16 mode);
BtlPacket* btlUnitCreateMovePacket(BtlUnit* unit, const RwV3d* targetPos, f32 speed, u32 flags);
BtlPacket* btlUnitCreateRotatePacket(BtlUnit* unit, const RwV3d* rot, u32 flags);
BtlPacket* btlUnitCreateRotateTowardUnitPacket(BtlUnit* unit, BtlUnit* targetUnit, u32 flags);
BtlPacket* btlUnit00286320(BtlUnit* unit);
BtlPacket* btlUnitCreateLookAtPacket(BtlUnit* unit, const RwV3d* targetPos, u16 flags);
BtlPacket* btlUnitCreateLookAtUnitPacket(BtlUnit* unit, BtlUnit* targetUnit, u16 flags);
BtlPacket* btlUnitCreateLookAtDeactivatePacket(BtlUnit* unit, u16 flags);
BtlPacket* btlUnitCreatePosRotColPacket(BtlUnit* unit, const RwV3d* pos, const RtQuat* rot, const RwRGBA* col);

#endif