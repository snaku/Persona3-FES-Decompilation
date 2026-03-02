#ifndef RESRCMANAGER_H
#define RESRCMANAGER_H

#include "Utils.h"

typedef enum
{
    // TODO

    RES_TYPE_MAX = 22
} ResourceType;

// 256 bytes. Base struct for every type of resource
typedef struct Resource
{
    u16 resTypeId;         // 0x00. bits 0-9 = id. bits 10-15 = type (See enum 'ResourceType')
    u8 unkData[0xf6];
    struct Resource* next; // 0xf8
    struct Resource* prev; // 0xfc
} Resource;

// 88 bytes
typedef struct ResManager
{
    Resource* resLists[RES_TYPE_MAX]; // 0x00. Head of list for every type of resource
} ResManager;

ResManager* ResManager_Init();

#endif