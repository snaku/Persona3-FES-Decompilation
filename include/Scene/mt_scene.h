#ifndef MT_SCENE_H
#define MT_SCENE_H

#include "Utils.h"

typedef struct ResrcManager ResrcManager;
typedef struct Resrc Resrc;
typedef struct HCdvd HCdvd;

// 40 bytes ? Not sure
typedef struct
{
    s32 fldMajorId;           // 0x00
    s32 fldMinorId;           // 0x04
    ResrcManager* resManager; // 0x08
    s32 unk_0c;               // 0x0c
    HCdvd* cmrCdvd;           // 0x10. Cdvd of "field/env/f*.CMR". Path doesn't exist, so never used
    u8 unkData[0x14];
} MtScene;

extern MtScene* gMtScene;

MtScene* MT_Scene_GetScene();
Resrc* MT_Scene_GetRes(u16 resTypeId);
Resrc* MT_Scene_GetResListHead(u32 resType);
u32 MT_Scene_GetTotalResInList(u32 resType);
u16 MT_Scene_CreateResLightParty(u16 id);

#endif