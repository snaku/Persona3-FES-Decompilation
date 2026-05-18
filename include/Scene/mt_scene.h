#ifndef MT_SCENE_H
#define MT_SCENE_H

#include "Utils.h"

typedef struct ResrcManager ResrcManager;
typedef struct Resrc Resrc;
typedef struct HCdvd HCdvd;
typedef struct KwlnTask KwlnTask;
typedef struct Model Model;

// 40 bytes ? Not sure
typedef struct
{
    s32 fldMajorId;           // 0x00
    s32 fldMinorId;           // 0x04
    ResrcManager* resManager; // 0x08
    s32 unk_0c;               // 0x0c
    HCdvd* cmrCdvd;           // 0x10. Cdvd of "field/env/f*.CMR". Path doesn't exist, so never used
    s32 unk_14;               // 0x14
    s32 unk_18;               // 0x18
    u32 inEvt;                // 0x1c. is currently in an event
    KwlnTask* sceneMngTask;   // 0x20
    KwlnTask* fldFilterTask;  // 0x24
} MtScene;

extern MtScene* gMtScene;

MtScene* MT_Scene_GetScene();

Resrc* MT_Scene_GetRes(u16 resTypeId);
Resrc* MT_Scene_GetResListHead(u32 resType);
u32 MT_Scene_GetTotalResInList(u32 resType);
u16 MT_Scene_CreateResModelChar(u16 resId, s32 param_2, Model* mdl);
u16 MT_Scene_CreateResModelNpc(u32 resId, u16 param_2, Model* mdl);
u16 MT_Scene_CreateResLightChar(u16 resId);
u16 MT_Scene_CreateResLightNpc(u16 resId);

#endif