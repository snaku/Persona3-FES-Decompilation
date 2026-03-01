#include "Scene/mt_scene.h"

static Mt_Scene sMtScene;       // 0095afc0
Mt_Scene* gMtScene = &sMtScene; // 007cd540

// FUN_003b5cf0
Mt_Scene* Mt_Scene_GetScene()
{
    return gMtScene;
}