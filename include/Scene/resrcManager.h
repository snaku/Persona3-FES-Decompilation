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
    RESRC_TYPE_MODELPARTY = 1,
    RESRC_TYPE_MODELUNK,
    RESRC_TYPE_MODELNPC,
    RESRC_TYPE_LIGHTPARTY,
    RESRC_TYPE_LIGHTNPC,
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
    u8 unkData[0xd0];
    Resrc* next;       // 0xf8
    Resrc* prev;       // 0xfc
};

// 496 bytes. Party resource
typedef struct ResrcModelParty
{
    Resrc base;                    // 0x00
    u8 unkData1[0x28];
    Model* mdl;                    // 0x128
    u8 unkData2[0xb4];
    KwlnTask* collisCtlTask;       // 0x1e0. Task for a 'FldFrame'
    KwlnTask* renderTexShadowTask; // 0x1e4
    u8 unkData3[0x08];
} ResrcModelParty;

// 544 bytes. NPC resource
typedef struct ResrcModelNpc
{
    Resrc base;        // 0x00
    u8 unkData1[0x28];
    Model* mdl;        // 0x128
    u8 unkData2[0xf4];
} ResrcModelNpc;

// 432 bytes. Lighting parameters resource for party
typedef struct ResrcLightParty
{
    Resrc base;                  // 0x00
    RwRGBAReal ambientColor;     // 0x100
    RwRGBAReal directionalColor; // 0x110
    RwMatrix directionalMat;     // 0x120
    u8 unkData1[0x50];
} ResrcLightParty;

// 432 bytes. Lighting parameters resource for npc's
typedef struct ResrcLightNpc
{
    Resrc base;                  // 0x00
    RwRGBAReal ambientColor;     // 0x100
    RwRGBAReal directionalColor; // 0x110
    RwMatrix directionalMat;     // 0x120
    u8 unkData1[0x50];
} ResrcLightNpc;

// 88 bytes
typedef struct ResrcManager
{
    Resrc* resLists[RESRC_TYPE_MAX]; // 0x00. Head of list for every type of resource
} ResrcManager;

ResrcManager* resrcMngInit();
void resrcMngDestroy(ResrcManager* resManager);
Resrc* resrcMngCreateRes(ResrcManager* resManager, u16 resTypeId);
void resrcMngDestroyRes(ResrcManager* resManager, Resrc* res);
Resrc* resrcMngGetListHead(ResrcManager* resManager, u8 resType);
Resrc* resrcMngGetListTail(ResrcManager* resManager, u8 resType);
Resrc* resrcMngGetRes(ResrcManager* resManager, u16 resTypeId);
u32 resrcMngGetTotalResInList(ResrcManager* resManager, u8 resType);

#endif