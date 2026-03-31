#ifndef K_FLDCAMERA_H
#define K_FLDCAMERA_H

#include "Utils.h"
#include "rw/rwplcore.h"

typedef enum
{
    // TODO
    FLDCAMERA_TYPE_0
} FieldCameraType;

// 112 bytes. Content of a .CMR file
typedef struct CmrFile
{
    u8 unkData1[0x08];
    f32 fov;           // 0x08. Fov in deg
    s32 unk_0c;        // 0x0c
    RwMatrix mat;      // 0x10
    u16 type;          // 0x50. See enum 'FieldCameraType'
    u8 unkData2[0x1e];
} CmrFile;

#endif