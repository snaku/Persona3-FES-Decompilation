#ifndef K_FLDCAMERA_H
#define K_FLDCAMERA_H

#include "Utils.h"
#include "rw/rwcore.h"

typedef struct ResrcModelParty ResrcModelParty;

typedef enum
{
    // TODO
    FLDCAMERA_TYPE_0
} FldCameraType;

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
    u8 unkData1[0x08];
    u32 type;                     // 0x08
    RwFrame* frame;               // 0x0c. Main frame of the field camera
    RwFrame* frame2;              // 0x10. Parent of the parent of RwCamera (idk why)
    u8 unkData2[0xb8];
    ResrcModelParty* playerResrc; // 0xcc
} FldCamera;

#endif