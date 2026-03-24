#ifndef MDLMANAGER_H
#define MDLMANAGER_H

#include "Utils.h"
#include "rw/rtquat.h"

typedef struct RwFrame RwFrame;
typedef struct RpClump RpClump;
typedef struct RpHAnimHierarchy RpHAnimHierarchy;
typedef struct RtAnimInterpolator RtAnimInterpolator;
typedef struct RtAnimAnimation RtAnimAnimation;

typedef struct H_Cdvd H_Cdvd;

#define MDL_CDVDREAD   0x01
#define MDL_NOCDVDREAD 0x00

#define MDL_FLAG_FULLSHADOW (1 << 0)  // 0x01
#define MDL_FLAG_NODRAW     (1 << 1)  // 0x02.  Don't draw the model
#define MDL_FLAG_ZTEST      (1 << 3)  // 0x08.  Depth testing
#define MDL_FLAG_ZWRITE     (1 << 4)  // 0x10
#define MDL_FLAG_CULLFRONT  (1 << 6)  // 0x40.  Use 'rwCULLMODEFRONT', otherwise 'rwCULLMODEBACK'
#define MDL_FLAG_FOG        (1 << 8)  // 0x100. Enable fog for the model
#define MDL_FLAG_STREAMDONE (1 << 12) // 0x1000
#define MDL_FLAG_CDVDREAD   (1 << 14) // 0x4000. Can read .RMD or .PAC file from CDVD

#define MDL_LOOKAT_FLAG_XYZCS    (1 << 5) // 0x20. Cutscenes
#define MDL_LOOKAT_FLAG_XYZ      (1 << 6) // 0x40
#define MDL_LOOKAT_FLAG_XY       (1 << 7) // 0x80
#define MDL_LOOKAT_FLAG_NOTARGET (1 << 8) // 0x100

typedef enum
{
    MODEL_TYPE_BTLCHAR = 1, // BC*.RMD    - "MODEL/PACK/"    (in .pac)
    MODEL_TYPE_ENEMY,       // EM*.RMD    - "MODEL/PACK/"    (in .pac)
    MODEL_TYPE_PERSONA,     // PS*.RMD    - "MODEL/PERSONA/"
    MODEL_TYPE_FLDOBJ,      // FOBJ*.RMD  - "FIELD/GRMD/"
    MODEL_TYPE_NPC,         // N*.RMD     - "MODEL/NPC/"
    MODEL_TYPE_WEAPON = 7,  // WP*.RMD    - "MODEL/WEAPON/"
    MODEL_TYPE_ENEMYSYMBOL, // ES*.RMD    - "MODEL/SYMBOL/"
    MODEL_TYPE_FLDCHAR,     // FC_*_*.RMD - "MODEL/FIELD/"
    MODEL_TYPE_WEAPONH,     // WP*_H.RMD  - "MODEL/WEAPON/"
    MODEL_TYPE_PERSONAFCL,  // FP*.RMD    - "MODEL/FACILITYP/"

    MODEL_TYPE_MAX = 12
} ModelType;

typedef struct Model Model;

// 80 bytes
typedef struct MdlAnimEntry
{
    RwMatrix identityMat;    // 0x00
    RtAnimAnimation* rtAnim; // 0x40
    u8 unkData[0x0c];
} MdlAnimEntry;

// 16 bytes
typedef struct MdlAnimEntryTable
{
    MdlAnimEntry* entries; // 0x00
    u16 count;             // 0x04
    u16 unk_06;            // 0x06
    u8 unkData[0x08];
} MdlAnimEntryTable;

// 76 bytes
typedef struct MdlAnim
{
    u32 flags;                      // 0x00
    s16 id;                         // 0x04
    f32 speed;                      // 0x08. How fast the animation is playing
    f32 currTime;                   // 0x0c
    s16 oldId;                      // 0x10
    f32 oldTime;                    // 0x14
    u16 blendFrameCount;            // 0x18
    f32 blendFactor;                // 0x1c
    RpHAnimHierarchy* hierarchy;    // 0x20
    RtAnimInterpolator* oldInterp;  // 0x24. Old animation data
    RtAnimInterpolator* nextInterp; // 0x28. Animation data of the next animation to play
    MdlAnimEntryTable* table;       // 0x2c
    void* unk_30;                   // 0x30
    u32 keyframeIdx;                // 0x34. Unknown purpose
    RwV3d keyframeVec;              // 0x38. Unknown purpose. Used in a RtAnimKeyFrameApplyCallBack func
    f32 unk_44;                     // 0x44
    f32 unk_48;                     // 0x48
} MdlAnim;

// 80 bytes
typedef struct MdlLookAt
{
    u16 flags;          // 0x00. See 'MDL_LOOKAT_FLAG_*'
    f32 blendRotFactor; // 0x04. ]0.0f;1.0f[ = smooth rot, 0.0f = no rot, 1.0f = instant rot
    f32 maxPitchAngle;  // 0x08. Max X rot angle (degrees)
    f32 maxYawAngle;    // 0x0c. Max Y rot angle (degrees)
    RtQuat rot;         // 0x10. Current rotation
    RtQuat targetRot;   // 0x20
    RwV3d targetScale;  // 0x30
    RwV3d targetPos;    // 0x3c
    s32 unk_48;         // 0x48
    s32 unk_4c;         // 0x4c
} MdlLookAt;

// 156 bytes. Maybe temp name
typedef struct MdlAnimSlot
{
    MdlAnim anim;      // 0x00
    MdlLookAt lookAt;  // 0x4c
} MdlAnimSlot;

// 12 bytes
typedef struct MdlAttachedWpn
{
    u8 flags;      // 0x00
    Model* wpnMdl; // 0x04
    s32 unk_08;    // 0x08. Always 500, 501 (-1 is base init value)
} MdlAttachedWpn;

// 8 bytes
typedef struct MdlRmdFileMemory
{
    void* memory; // 0x00. Loaded .RMD file in memory
    u32 size;     // 0x04. Size of .RMD file in bytes
} MdlRmdFileMemory;

// 80 bytes
typedef struct MdlStream
{
    RwStream* rws;        // 0x00
    u8 unkData1[0x08];
    void* unk_0c;         // 0x0c
    u8 unkData2[0x28];
    MdlRmdFileMemory rmd; // 0x38
    s32 unk_40;           // 0x40
    H_Cdvd* cdvd;         // 0x44
    u8 unk_48;            // 0x48
    u32 isInPacFile;      // 0x4c
} MdlStream;

// 1072 bytes
struct Model
{
    RwMatrix mat;                   // 0x00
    RwMatrix identityMat;           // 0x40
    u8 unkData1[0x50];
    RwRGBA color;                   // 0xd0
    u16 type;                       // 0xd4. See enum 'ModelType'
    u16 id;                         // 0xd6. Usually, ids are linear. For 'MODEL_TYPE_FLDCHAR', id is composite (see 'MDL_FLDCHAR_*' macros)
    u16 flags;                      // 0xd8. See 'MDL_FLAG_*'
    RpClump* clump;                 // 0xdc
    void* unk_e0;                   // 0xe0
    u32 gsAlpha1Reg;                // 0xe4. ALPHA_1 GS register value to set
    u32 gsTest1Reg;                 // 0xe8. TEST_1 GS register value to set
    MdlAnimSlot animSlots[4];       // 0xec
    void* unk_35c;                  // 0x35c
    u8 unkData2[0x54];
    MdlAttachedWpn attachedWpns[5]; // 0x3b4. Only for 'MODEL_TYPE_BTLCHAR'
    u8 unkData3[0x30];
    Model* next;                    // 0x420
    Model* prev;                    // 0x424
    MdlStream* stream;              // 0x428
    u8 unkData4[0x08];
};

extern const f32 gFrameDuration;

Model* MdlManager_InitMdl(u16 type, u16 id);
Model* MdlManager_Search(u16 type, u16 id, u16 flags);
Model* MdlManager_CreateMdlFromPath(u16 type, u16 id, const char* path, u32 cdvdRead);
Model* MdlManager_CreateMdlFromRmdMemory(u16 type, u16 id, void* rmdMemory, u32 rmdSize, u32 cdvdRead);
Model* MdlManager_CreateMdlAndResolvePath(u16 type, u16 id, u32 cdvdRead);

f32 MdlAnim_GetDurationInFrame(Model* mdl, u16 slotIdx);
f32 MdlAnim_GetDurationInFrameById(Model* mdl, u16 slotIdx, s16 animId);
f32 MdlAnim_GetCurrentFrame(Model* mdl, u16 slotIdx);

void Mdl_SetColor(Model* mdl, RwRGBA* color);
RwRGBA* Mdl_GetColor(Model* mdl);
RwMatrix* Mdl_GetMatrix(Model* mdl);
RwFrame* Mdl_GetClumpFrame(Model* mdl);
RpClump* Mdl_GetClump(Model* mdl);
void Mdl_EnableFullShadow(Model* mdl);
void Mdl_DisableFullShadow(Model* mdl);

void MdlLookAt_SetBlendRotFactor(Model* mdl, f32 blendRotFactor);
void MdlLookAt_SetMaxAngles(Model* mdl, f32 maxPitchAngle, f32 maxYawAngle);
void MdlLookAt_SetTargetPosXYZ(Model* mdl, RwV3d* target);
void MdlLookAt_SetTargetPosXYZCS(Model* mdl, RwV3d* target);
void MdlLookAt_SetTargetPosXY(Model* mdl, f32 xTarget, f32 yTarget);
void MdlLookAt_DisableTarget(Model* mdl);
u8 MdlLookAt_IsActive(Model* mdl);
void MdlLookAt_SetTargetScale(Model* mdl, RwV3d* scale);

#endif