#ifndef MT_SCENE_H
#define MT_SCENE_H

#include "Utils.h"

typedef struct ResManager ResManager;
typedef struct Resource Resource;

// 40 bytes ? Not sure
typedef struct
{
    s32 fldMajorId;         // 0x00
    s32 fldMinorId;         // 0x04
    ResManager* resManager; // 0x08
    u8 unkData[0x1c];
} MtScene;

extern MtScene* gMtScene;

MtScene* MT_Scene_GetScene();
Resource* MT_Scene_GetRes(u16 resTypeId);
Resource* MT_Scene_GetResListHead(u32 resType);

#endif