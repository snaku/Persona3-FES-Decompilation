#ifndef MDLMANAGER_H
#define MDLMANAGER_H

#include "Utils.h"
#include "rw/rtquat.h"

typedef struct RpClump RpClump;

#define MDL_RENDER_FLAG_NODRAW    (1 << 1)  // 0x02.  Don't draw the model (not 100% sure about this one)
#define MDL_RENDER_FLAG_ZTEST     (1 << 3)  // 0x08.  Depth testing
#define MDL_RENDER_FLAG_ZWRITE    (1 << 4)  // 0x10
#define MDL_RENDER_FLAG_CULLFRONT (1 << 6)  // 0x40.  Use 'rwCULLMODEFRONT', otherwise 'rwCULLMODEBACK'
#define MDL_RENDER_FLAG_FOG       (1 << 8)  // 0x100. Enable fog for the model

#define MDL_LOOKAT_FLAG_XYZCS    (1 << 5) // 0x20. Cutscenes
#define MDL_LOOKAT_FLAG_XYZ      (1 << 6) // 0x40
#define MDL_LOOKAT_FLAG_XY       (1 << 7) // 0x80
#define MDL_LOOKAT_FLAG_NOTARGET (1 << 8) // 0x100

typedef enum
{
    MODEL_TYPE_BTLCHAR = 1, // BC*.RMD    - "MODEL/PACK/" (in .pac)
    MODEL_TYPE_ENEMY,       // EM*.RMD    - "MODEL/PACK/" (in .pac)
    MODEL_TYPE_PERSONA,     // PS*.RMD    - "MODEL/PERSONA/"
    MODEL_TYPE_NPC = 5,     // N*.RMD     - "MODEL/NPC/"
    MODEL_TYPE_WEAPON = 7,  // WP*.RMD    - "MODEL/WEAPON/"
    MODEL_TYPE_ENEMYSYMBOL, // ES*.RMD    - "MODEL/SYMBOL/"
    MODEL_TYPE_FLDCHAR,     // FC_*_*.RMD - "MODEL/FIELD/"
    MODEL_TYPE_WEAPONH,     // WP*_H.RMD  - "MODEL/WEAPON/"
    MODEL_TYPE_PERSONAFCL   // FP*.RMD    - "MODEL/FACILITYP/"
} ModelType;

// ?? bytes (TBD)
typedef struct MdlAnim
{
    u8 unkData1[0x08];
    f32 speed;         // 0x08. How fast the animation is playing
    f32 currTime;      // 0x0c
} MdlAnim;

// ?? bytes (TBD, currently 72 bytes)
typedef struct MdlLookAt
{
    u16 flags;          // 0x00. See 'MDL_LOOKAT_FLAG_*'
    f32 blendRotFactor; // 0x04. ]0.0f;1.0f[ = smooth rot, 0.0f = no rot, 1.0f = instant rot
    f32 maxPitchAngle;  // 0x08. Max X rot angle (degrees)
    f32 maxYawAngle;    // 0x0c. Max Y rot angle (degrees)
    RtQuat rot;         // 0x10
    u8 unkData[0x10];
    RwV3d scale;        // 0x30
    RwV3d target;       // 0x3c
} MdlLookAt;

// 1072 bytes
typedef struct Model
{
    RwMatrix mat;      // 0x00
    u8 unkData1[0x90];
    RwRGBA color;      // 0xd0
    u16 type;          // 0xd4. See enum 'ModelType'
    u16 id;            // 0xd6. Usually, ids are linear. For 'MODEL_TYPE_FLDCHAR', id is composite (see 'MDL_FLDCHAR_*' macros)
    u16 renderFlag;    // 0xd8. See 'MDL_RENDER_FLAG_*'
    RpClump* clump;    // 0xdc
    u8 unkData2[0x0c];
    MdlAnim anim;      // 0xec
    u8 unkData3[0x3c];
    MdlLookAt lookAt;  // 0x138
    u8 unkDat4[0x2b0];
} Model;

Model* MdlManager_InitMdl(u32 type, u32 id);
Model* MdlManager_CreateMdl(u32 type, u32 id, u32 flags);

void Mdl_SetColor(Model* mdl, RwRGBA* color);
RwRGBA* Mdl_GetColor(Model* mdl);
RwMatrix* Mdl_GetMatrix(Model* mdl);
RwFrame* Mdl_GetClumpFrame(Model* mdl);
RpClump* Mdl_GetClump(Model* mdl);

void MdlLookAt_SetTargetXYZ(Model* mdl, RwV3d* target);
void MdlLookAt_DisableTarget(Model* mdl);
u8 MdlLookAt_IsActive(Model* mdl);

#endif