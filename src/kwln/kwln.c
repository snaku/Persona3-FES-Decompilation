#include "kwln/kwln.h"
#include "rw/rwplcore.h"

static RwCamera* sMainCamera;   // 007ce0c0
static KwlnTask* sRootProcTask; // 007ce0d0
u32 gFogEnabled;                // 007ce0d4
u8 gFogRed;                     // 007ce0d8
static u8 sbssPad1[0x03];
u8 gFogBlue;                    // 007ce0dc
static u8 sbssPad2[0x03];
u8 gFogGreen;                   // 007ce0e0
static u8 sbssPad3[0x03];
u8 gFogAlpha;                   // 007ce0e4
static RwRGBA sClearColor;      // 007ce128

// FUN_00198590
RwCamera* Kwln_GetMainCamera()
{
    return sMainCamera;
}

// FUN_001985a0
RwRGBA* Kwln_GetClearColor()
{
    return &sClearColor;
}

// FUN_001985b0
void Kwln_SetClearColor(u8 r, u8 g, u8 b, u8 a)
{
    sClearColor.r = r;
    sClearColor.g = g;
    sClearColor.b = b;
    sClearColor.a = a;
}