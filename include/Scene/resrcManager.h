#ifndef RESRCMANAGER_H
#define RESRCMANAGER_H

#include "Utils.h"

typedef struct KwlnTask KwlnTask;

#define RES_TYPE_MASK 0xffc00
#define RES_GET_TYPE(resTypeId) (((resTypeId) & RES_TYPE_MASK) >> 10)

typedef enum
{
    // TODO
    RES_TYPE_DYNAMIC = 1,
    RES_TYPE_UNK,
    RES_TYPE_NPC,
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

// 496 bytes. Dynamic resource (TODO: find a better name)
typedef struct ResourceDynamic
{
    Resource base;                 // 0x00
    u8 unkData1[0xe0];
    KwlnTask* colliCtlTask;        // 0x1e0
    KwlnTask* renderTexShadowTask; // 0x1e4
    u8 unkData[0x08];
} ResourceDynamic;

// 544 bytes. NPC resource
typedef struct ResourceNpc
{
    Resource base;
    u8 unkData[0x120];
} ResourceNpc;

// 88 bytes
typedef struct ResManager
{
    Resource* resLists[RES_TYPE_MAX]; // 0x00. Head of list for every type of resource
} ResManager;

ResManager* ResManager_Init();
void ResManager_Destroy(ResManager* resManager);
void ResManager_DestroyRes(ResManager* resManager, Resource* res);
Resource* ResManager_GetListHead(ResManager* resManager, u8 resType);
Resource* ResManager_GetListTail(ResManager* resManager, u8 resType);
Resource* ResManager_GetRes(ResManager* resManager, u16 resTypeId);
u32 ResManager_GetTotalResInList(ResManager* resManager, u8 resType);

#endif