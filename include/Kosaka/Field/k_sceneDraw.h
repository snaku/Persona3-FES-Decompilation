#ifndef K_SCENEDRAW_H
#define K_SCENEDRAW_H

#include "Utils.h"

typedef struct KwlnTask KwlnTask;
typedef struct RwRGBAReal RwRGBAReal;

KwlnTask* K_SceneDraw_CreateTasks(KwlnTask* rootProcTask);

RwRGBAReal* K_Scene_GetFldAmbLightColor();
RwRGBAReal* K_Scene_GetCharAmbLightColor();
u32 K_Scene_001a0250();
void K_Scene_SetShouldSortChars(u32 shouldSortChars);
void K_Scene_SetShouldSortNpcs(u32 shouldSortNpcs);
void K_Scene_InitCharLight();
void K_Scene_InitNpcLight();

#endif