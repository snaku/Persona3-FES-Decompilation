#ifndef MDLEFFECT_H
#define MDLEFFECT_H

#include "Utils.h"
#include "rw/rw.h"

typedef struct mdlEffect
{
    u16 word0;            // 0x00
    INSERT_PADDING(0x2);  // 0x02
    u32 dword4;           // 0x04
    u16 word8;            // 0x08
    u16 wordA;            // 0x0a
    RwFrame* frame;       // 0x0c
    RpAtomic* atomic;     // 0x10
    u32 dword14;          // 0x14
    u32 dword18;          // 0x18
    u16 word1C;           // 0x1c
    u16 numVerts;         // 0x1e
    u16 numTriangles;     // 0x20
    u8 byte22;            // 0x22
    u8 byte23;            // 0x23
    u8 byte24;            // 0x24
    u8 byte25;            // 0x25
    INSERT_PADDING(0x2);  // 0x26
    RpMaterial* material; // 0x28
} mdlEffect;

// 8 bytes
typedef struct mdlEffectSkyRenderStateTblEntry
{
    s16 atest1;          // 0x00
    INSERT_PADDING(0x2); // 0x02
    s32 alpha1;          // 0x04
} mdlEffectSkyRenderStateTblEntry;

// 24 bytes
typedef struct mdlEffectRwRenderStateTblEntry
{
    s32 states[3]; // 0x00
} mdlEffectRwRenderStateTblEntry;

// 160 bytes
typedef struct mdlEffectListEntry
{
    RwV3d translation;    // 0x00
    INSERT_PADDING(0x88); // 0x0c
    Model* model;         // 0x94
    INSERT_PADDING(0x4);  // 0x98
    s32 next;             // 0x9c
} mdlEffectListEntry;

// 24 bytes
typedef struct mdlEffectScreenEffectTblEntry
{
    s32 init;            // 0x00
    s32 destroy;         // 0x04
    s32 update;          // 0x08
    s32 draw;            // 0x0c
    char flag;           // 0x10
    INSERT_PADDING(0x3); // 0x11
    s32 structSize;      // 0x14
} mdlEffectScreenEffectTblEntry;

// 52 bytes
typedef struct mdlEffectMainTblEntry
{
    s32 init;    // 0x00
    s32 update;  // 0x04
    s32 update2; // 0x08
    s32 func_C;  // 0x0c
    s32 destroy; // 0x10
    s32 init2;   // 0x14
    s32 func_18; // 0x18
    s32 func_1C; // 0x1c
    s32 func_20; // 0x20
    s32 func_24; // 0x24
    s32 func_28; // 0x28
    s32 func_2C; // 0x2c
    s32 func_30; // 0x30
} mdlEffectMainTblEntry;

// 48 bytes
typedef struct mdlEffectScreenEffectSubtypeWork
{
    char char0;                          // 0x00
    INSERT_PADDING(0xF);                 // 0x01
    u32 dword10;                         // 0x10
    f32 dword14;                         // 0x14
    u32 type;                            // 0x18
    INSERT_PADDING(0x4);                 // 0x1c
    u32 func0Result;                     // 0x20
    void* subtypeData;                   // 0x24
    mdlEffectLoadedTexture* textureData; // 0x28
    u32 dword2C;                         // 0x2c
    char subtypeDataBuf[];               // 0x30
} mdlEffectScreenEffectSubtypeWork;

// 44 bytes
typedef struct mdlEffectEffectWork
{
    INSERT_PADDING(0xC);       // 0x00
    s16 subtype;               // 0x0c
    INSERT_PADDING(0x2);       // 0x0e
    s32 subtypeDataOfs;        // 0x10
    INSERT_PADDING(0x4);       // 0x14
    s32 subtypeId;             // 0x18
    s32 textureFileType;       // 0x1c
    s32 textureDataOfs;        // 0x20
    INSERT_PADDING(0x4);       // 0x24
    s32 textureDataIsAbsolute; // 0x28
} mdlEffectEffectWork;

// 12 bytes
typedef struct mdlEffectLoadedTexture
{
    char textureFileType; // 0x00
    INSERT_PADDING(0x3);  // 0x01
    u32 dword4;           // 0x04
    RwTexture* texture;   // 0x08
} mdlEffectLoadedTexture;

// 40 bytes
typedef struct mdlEffectScreenEffectParams
{
    RwRGBA color;        // 0x00
    RwReal scale;        // 0x04
    RwReal angleRad;     // 0x08
    INSERT_PADDING(0x4); // 0x0c
    RwReal xPixelOfs;    // 0x10
    RwReal yPixelOfs;    // 0x14
    RwReal x0;           // 0x18
    RwReal y0;           // 0x1c
    RwReal x1;           // 0x20
    RwReal y1;           // 0x24
} mdlEffectScreenEffectParams;

// 44 bytes
typedef struct mdlEffectDraw2PassScreenEffectParams
{
    INSERT_PADDING(0x4);                            // 0x00
    mdlEffectScreenEffectParams screenEffectParams; // 0x04
} mdlEffectDraw2PassScreenEffectParams;

// 52 bytes
typedef struct mdlEffectScreenEffectType7ListEntry
{
    s32 timer;                     // 0x00
    INSERT_PADDING(0x4);           // 0x04
    s32 twoPassScreenEffectParams; // 0x08
    INSERT_PADDING(0x3);           // 0x0c
    char drawFlag2;                // 0x0f
    INSERT_PADDING(0x24);          // 0x10
} mdlEffectScreenEffectType7ListEntry;

// 236 bytes
typedef struct mdlEffectScreenEffectType7ListHeader
{
    INSERT_PADDING(0xC0); // 0x00
    s32 entryCount;       // 0xc0
    INSERT_PADDING(0x8);  // 0xc4
    s32 flags;            // 0xcc
    INSERT_PADDING(0x1C); // 0xd0
} mdlEffectScreenEffectType7ListHeader;

// 196 bytes
typedef struct mdlEffectScreenEffectType7Params
{
    INSERT_PADDING(0x20);                                  // 0x00
    mdlEffectScreenEffectType7ListEntry* entries;          // 0x20
    mdlEffectScreenEffectType7ListHeader* entryListHeader; // 0x24
    mdlEffectScreenEffectType7Params28* textureDataHolder; // 0x28
    INSERT_PADDING(0x94);                                  // 0x2c
    s32 entryCount;                                        // 0xc0
} mdlEffectScreenEffectType7Params;

// 12 bytes
typedef struct mdlEffectScreenEffectType7Params28
{
    INSERT_PADDING(0x8); // 0x00
    s32 textureData;     // 0x08
} mdlEffectScreenEffectType7Params28;

void mdlEffect00321120(u16 param_1);

#endif