#ifndef MT_SCENE_H
#define MT_SCENE_H

#include "Utils.h"

typedef struct ResManager ResManager;

// 40 bytes ? Not sure
typedef struct
{
    s32 fldMajorId;         // 0x00
    s32 fldMinorId;         // 0x04
    ResManager* resManager; // 0x08
    u8 unkData[0x1c];
} Mt_Scene;

extern Mt_Scene* gMtScene;

Mt_Scene* Mt_Scene_GetScene();

#endif