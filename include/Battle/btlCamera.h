#ifndef BTLCAMERA_H
#define BTLCAMERA_H

#include "Utils.h"
#include "Battle/btlPacket.h"
#include "rw/rtquat.h"

#define BTLCAMERA_FLAG_FREEZE (1 << 0) // 0x01
#define BTLCAMERA_FLAG_UNK02  (1 << 1) // 0x02

typedef struct BtlAction BtlAction;

typedef enum
{
    BTLCAMERA_STATE_NULL,
    BTLCAMERA_STATE_NOP,
    BTLCAMERA_STATE_ENCOUNT,
    BTLCAMERA_STATE_ANALYZE,
    BTLCAMERA_STATE_ASSIST,
    BTLCAMERA_STATE_REINFORCE,
    BTLCAMERA_STATE_ROUNDUP,
    BTLCAMERA_STATE_ESCAPE,
    BTLCAMERA_STATE_ESCAPEMES,
    BTLCAMERA_STATE_OWN,
    BTLCAMERA_STATE_ATTACKSHORT,
    BTLCAMERA_STATE_ATTACKLONG,
    BTLCAMERA_STATE_ATTACKDOWN_P,
    BTLCAMERA_STATE_ATTACKDOWN_E,
    BTLCAMERA_STATE_ATTACKSLIP,
    BTLCAMERA_STATE_ATTACKCOMB,
    BTLCAMERA_STATE_SKILLRECITE_P,
    BTLCAMERA_STATE_SKILLRECITE_E,
    BTLCAMERA_STATE_MOVETARGET,
    BTLCAMERA_STATE_MOVETARET_A,
    BTLCAMERA_STATE_MOVEHOME,
    BTLCAMERA_STATE_SKILLEXEC_PC,
    BTLCAMERA_STATE_SKILLEXEC_EC,
    BTLCAMERA_STATE_SKILLEXEC_ONE,
    BTLCAMERA_STATE_SKILLEXEC_REC,
    BTLCAMERA_STATE_SKILLEXEC_PS,
    BTLCAMERA_STATE_PERSONA,
    BTLCAMERA_STATE_OVERLIMIT,
    BTLCAMERA_STATE_COMMAND,
    BTLCAMERA_STATE_TARGET,
    BTLCAMERA_STATE_FREE,
    BTLCAMERA_STATE_RESET,
    BTLCAMERA_STATE_WIN,
    BTLCAMERA_STATE_CONDITION,
    BTLCAMERA_STATE_ORDER,
    BTLCAMERA_STATE_CHANGEFORM,
    BTLCAMERA_STATE_NYXFEATHER,
    BTLCAMERA_STATE_ALL,
    BTLCAMERA_STATE_ENEMYALL,
    BTLCAMERA_STATE_TARGETONLY,

    BTLCAMERA_STATE_MAX
} BtlCameraState;

// 28 bytes
typedef struct BtlCameraKeyFrame
{
    RwV3d pos;  // 0x00
    RtQuat rot; // 0x0c
} BtlCameraKeyFrame;

// at least 256 bytes
typedef struct BtlCamera
{
    s32 unk_00;                     // 0x00
    BtlCameraKeyFrame keyFrames[4]; // 0x04
    u16 keyFrameIdx;                // 0x74
    u8 unkData1[0x26];
    RwV3d pos;                      // 0x9c
    RtQuat rot;                     // 0xa8
    f32 fovRad;                     // 0xb8
    u8 unkData2[0x14];
    u16 state;                      // 0xd0. See enum 'BtlCameraState'
    u32 flags;                      // 0xd4
    s32 updateCounter;              // 0xd8
    s32 framesUntilUpdate;          // 0xdc
    BtlAction* action;              // 0xe0
    u8 unkData3[0x1c];
} BtlCamera;

// 20 bytes
typedef struct BtlCameraStateEntry
{
    void (*init)(BtlCamera* camera);   // 0x00
    void (*update)(BtlCamera* camera); // 0x04
    u32 unk_08;                        // 0x08
    u32 unk_0c;                        // 0x0c
    const char* name;                  // 0x10
} BtlCameraStateEntry;

typedef enum
{
    BTLCAMERA_PACKET_SETSTATE = BTLPACKET_MAKE_ID(BTLPACKET_MODULE_CAMERA, 0),
    BTLCAMERA_PACKET_MOVETO = BTLPACKET_MAKE_ID(BTLPACKET_MODULE_CAMERA, 1),
} BtlCameraPacket;

// 8 bytes
typedef struct BtlCameraPacketSetState
{
    BtlAction* action; // 0x00
    u16 state;         // 0x04
} BtlCameraPacketSetState;

// 60 bytes
typedef struct BtlCameraPacketMoveTo
{
    BtlAction* action;     // 0x00
    RwV3d startPos;        // 0x04
    RwV3d startTarget;     // 0x10
    RwV3d endPos;          // 0x1c
    RwV3d endTarget;       // 0x28
    f32 duration;          // 0x34
    u32 currPosAsStart; // 0x38
} BtlCameraPacketMoveTo;

void btlCameraMain();
void btlCameraDebugDraw();
void btlCameraFreeze();

BtlPacket* btlCameraCreateSetStatePacket(BtlAction* action, u16 state);
BtlPacket* btlCameraCreateMoveToPacket(BtlAction* action, const RwV3d* startPos, const RwV3d* startTarget, const RwV3d* endPos, const RwV3d* endTarget, f32 duration);

#endif