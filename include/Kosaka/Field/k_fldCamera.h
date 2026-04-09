#ifndef K_FLDCAMERA_H
#define K_FLDCAMERA_H

#include "Utils.h"
#include "rw/rwcore.h"

#define FLDCAMERA_FLAG_DRAWDEADZONE (1 << 31) // 0x80000000. Draw a cylinder that represents the current deadzone

typedef struct ResrcModelParty ResrcModelParty;

typedef enum
{
    // TODO
    FLDCAMERA_TYPE_0
} FldCameraType;

typedef enum
{
    FLDCAMERA_STATE_UPDATE,
    FLDCAMERA_STATE_IDLE
} FldCameraState;

// 112 bytes. Content of a '.CMR' file
typedef struct CmrFile
{
    u8 unkData1[0x08];
    f32 fov;           // 0x08. Fov in deg
    s32 unk_0c;        // 0x0c
    RwMatrix mat;      // 0x10
    u16 type;          // 0x50. See enum 'FieldCameraType'
    u8 unkData2[0x1e];
} CmrFile;

// 208 bytes. Work Data for "field camera controler" task
typedef struct FldCamera
{
    u32 state;                    // 0x00. See 'FldCameraState' enum
    u32 flags;                    // 0x04. See 'FLDCAMERA_FLAG_*'
    u32 type;                     // 0x08
    RwFrame* frame;               // 0x0c. Main frame of the field camera
    RwFrame* frame2;              // 0x10. Parent of the parent of RwCamera (idk why)
    RwV3d offset;                 // 0x14
    f32 xzDeadZone;               // 0x20. Horizontal deadzone
    f32 yDeadZone;                // 0x24. Vertical deadzone
    u8 unkData3[0xa4];
    ResrcModelParty* playerResrc; // 0xcc
} FldCamera;

#endif