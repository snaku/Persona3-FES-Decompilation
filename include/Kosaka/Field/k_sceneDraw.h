#ifndef K_SCENEDRAW_H
#define K_SCENEDRAW_H

#include "Utils.h"

typedef struct KwlnTask KwlnTask;
typedef struct RwRGBAReal RwRGBAReal;

KwlnTask* K_SceneDraw_CreateTasks(KwlnTask* rootProcTask);

RwRGBAReal* K_Scene_GetFldAmbLightColor();
RwRGBAReal* K_Scene_GetPartyAmbLightColor();
u32 K_Scene_001a0250();

#endif