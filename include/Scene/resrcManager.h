#ifndef RESRCMANAGER_H
#define RESRCMANAGER_H

#include "Utils.h"
#include "rw/rwplcore.h"

typedef struct KwlnTask KwlnTask;
typedef struct Model Model;

#define RESRC_ID_MASK   0x3ff
#define RESRC_TYPE_MASK 0xffc00
#define RESRC_GET_ID(resTypeId)           ((resTypeId) & RESRC_ID_MASK)
#define RESRC_GET_TYPE(resTypeId)         (((resTypeId) & RESRC_TYPE_MASK) >> 10)
#define RESRC_MAKE_TYPEID(resId, resType) (RESRC_GET_ID((resId)) | ((resType) << 10))

typedef enum
{
    // TODO
    RESRC_TYPE_MODELCHAR = 1,
    RESRC_TYPE_MODELUNK,
    RESRC_TYPE_MODELNPC,
    RESRC_TYPE_LIGHTCHAR,
    RESRC_TYPE_LIGHTNPC,
    RESRC_TYPE_MODELFLD = 10,
    RESRC_TYPE_FLD = 12,
    RESRC_TYPE_FLDHIT,
    RESRC_TYPE_MAX = 22
} ResrcType;

typedef struct Resrc Resrc;

// 256 bytes. Base struct for every type of resource
struct Resrc
{
    u16 resTypeId;     // 0x00. bits 0-9 = id. bits 10-15 = type (See enum 'ResrcType')
    u8 unkData1[0x1a];
    f32 unk_1c;        // 0x1c
    f32 unk_20;        // 0x20
    f32 unk_24;        // 0x24
    u32 flags;         // 0x28
    u8 unkData[0xcc];
    Resrc* next;       // 0xf8
    Resrc* prev;       // 0xfc
};

// 496 bytes. Character resource
typedef struct ResrcModelChar
{
    Resrc base;                    // 0x00
    u8 unkData1[0x28];
    Model* mdl;                    // 0x128
    u8 unkData2[0xb4];
    KwlnTask* collisCtlTask;       // 0x1e0
    KwlnTask* renderTexShadowTask; // 0x1e4
    Model* baseMdl;                // 0x1e8. Base model (field/base.RMD)       
    Model* unkMdl;                 // 0x1ec
} ResrcModelChar;

// 544 bytes. NPC resource
typedef struct ResrcModelNpc
{
    Resrc base;                    // 0x00
    u8 unkData1[0x28];
    Model* mdl;                    // 0x128
    u8 unkData2[0xbc];
    KwlnTask* collisCtlTask;       // 0x1e8
    Model* baseMdl;                // 0x1ec. Base model (field/base.RMD) 
    KwlnTask* renderTexShadowTask; // 0x1f0
    u8 unkData3[0x2c];
} ResrcModelNpc;

// 432 bytes. Lighting parameters resource for characters
typedef struct ResrcLightChar
{
    Resrc base;                  // 0x00
    RwRGBAReal ambientColor;     // 0x100
    RwRGBAReal directionalColor; // 0x110
    RwMatrix directionalMat;     // 0x120
    u8 unkData1[0x50];
} ResrcLightChar;

// 432 bytes. Lighting parameters resource for npcs
typedef struct ResrcLightNpc
{
    Resrc base;          // 0x00
    RwRGBAReal ambColor; // 0x100
    RwRGBAReal dirColor; // 0x110
    RwMatrix dirMat;     // 0x120
    u8 unkData1[0x50];
} ResrcLightNpc;

// 304 bytes
typedef struct ResrcModelFld
{
    Resrc base;       // 0x00
    s32 unk_100;      // 0x100
    Model* mdl;       // 0x104
    u8 unkData[0x28];
} ResrcModelFld;

// 368 bytes. Field resource
typedef struct ResrcFld
{
    Resrc base;               // 0x00
    RwRGBAReal ambLightColor; // 0x100
    RwRGBAReal dirLightColor; // 0x110
    RwMatrix dirLightMat;     // 0x120
    void* unk_160;            // 0x160
    u8 unkData[0x0c];
} ResrcFld;

// 336 bytes
typedef struct ResrcFldHit
{
    Resrc base;        // 0x00
    u8 unkData1[0x1c];
    RwV3d vertices[4]; // 0x11c
    s32 unk_14c;       // 0x14c
} ResrcFldHit;

// 88 bytes
typedef struct ResrcManager
{
    Resrc* resLists[RESRC_TYPE_MAX]; // 0x00. Head of list for every type of resource
} ResrcManager;

ResrcManager* resrcMngCreate();
void resrcMngDestroy(ResrcManager* resManager);
Resrc* resrcMngCreateRes(ResrcManager* resManager, u16 resTypeId);
void resrcMngDestroyRes(ResrcManager* resManager, Resrc* res);
Resrc* resrcMngGetListHead(ResrcManager* resManager, u8 resType);
Resrc* resrcMngGetListTail(ResrcManager* resManager, u8 resType);
Resrc* resrcMngGetRes(ResrcManager* resManager, u16 resTypeId);
u32 resrcMngGetTotalResInList(ResrcManager* resManager, u8 resType);

#endif