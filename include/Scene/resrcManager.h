#ifndef RESRCMANAGER_H
#define RESRCMANAGER_H

#include "Utils.h"

// 88 bytes
typedef struct
{
    u8 unkData[0x58];
} ResManager;

ResManager* ResManager_Create();

#endif