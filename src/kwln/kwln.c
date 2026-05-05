#include "kwln/kwln.h"
#include "kwln/kwlnTask.h"
#include "kwln/kwlnRoot.h"
#include "rw/rpworld.h"
#include "rw/rprandom.h"
#include "sce/eekernel.h"
#include "sce/eeregs.h"

static RwRGBA sClearColor;         // 007ce128
static u32 sFrameCount2;           // 007ce10c
static u32 sFrameCount;            // 007ce108
u32 gT0CountVal;                   // 007ce0fc. Current value of T0_COUNT reg
u8 gFogAlpha;                      // 007ce0e4
static u8 sbssPad3[0x03];
u8 gFogGreen;                      // 007ce0e0
static u8 sbssPad2[0x03];
u8 gFogBlue;                       // 007ce0dc
static u8 sbssPad1[0x03];
u8 gFogRed;                        // 007ce0d8
u32 gFogEnabled;                   // 007ce0d4
static KwlnTask* sRootTask;        // 007ce0d0
u32 gCurrWorldIdx;                 // 007ce0cc. always 0
static s32 sMainThreadId;          // 007ce0c8
static RwCamera* sMainCamera;      // 007ce0c0
static RpLight* sDirectionalLight; // 007ce0ac
static RpLight* sAmbientLight;     // 007ce0a8
static RpWorld* sWorlds[2];        // 007ce0a0. Only the first index is used
static u64 sT0Count64;             // 007ce098

// a lot of them are probably temporary here
const f32 g18deg = gPI / 10;              // 007caf00
const f32 gRadToDegFactor = 180.0f / gPI; // 007caea8
const f32 gPI = 3.14159274;               // 007cae58
const f32 gAspectRatio = 4.0f / 3.0f;     // 007cad1c

// FUN_00195de0
void kwlnInitGameData()
{
    // TODO
}

// FUN_00196fe0
s32 kwlnT0OverflowHandler(s32 intc)
{
    if (intc == INTC_TIM0 && 
       (DGET_T0_MODE() & (1 << T_MODE_OVFF_O)))
    {
        DGET_T0_MODE() |= (1 << T_MODE_OVFF_O);

        sT0Count64 += 0x10000;
    }

    ExitHandler();

    return 0;
}

// FUN_00197030. HPad, memcard and IOP module init
void kwlnInitEE()
{
    // TODO
}

// FUN_00197350. Renderware init (engine, camera, lights etc...)
void kwlnInitRenderer()
{
    // TODO
}

// FUN_00198010. A lot of random init (CRI ROFS, admini task, dbprt etc...)
void kwln00198010()
{
    // TODO
}

// FUN_001983a0
u8 kwlnUpdate()
{
    // TODO

    return true;
}

// FUN_001984c0. Initialize everything + main loop
void kwlnMain()
{
    kwlnInitEE();
    kwlnInitRenderer();
    kwln00198010();

    while (true)
    {
        sRootTask = kwlnRootCreateTask();
        
        kwlnInitGameData();

        RpRandomSeed(DGET_T0_COUNT());
        RpRandomSeedMT(DGET_T0_COUNT());

        // main loop
        while (kwlnTaskExists(sRootTask))
        {
            kwlnUpdate();
        }
    }
}

// FUN_00198540
RpWorld* kwlnGetWorld(u32 worldIdx)
{
    return sWorlds[worldIdx];
}

// FUN_00198560
RpLight* kwlnGetAmbientLight()
{
    return sAmbientLight;
}

// FUN_00198570
RpLight* kwlnGetDirectionalLight()
{
    return sDirectionalLight;
}

// FUN_00198590
RwCamera* kwlnGetMainCamera()
{
    return sMainCamera;
}

// FUN_001985a0
RwRGBA* kwlnGetClearColor()
{
    return &sClearColor;
}

// FUN_001985b0
void kwlnSetClearColor(u8 r, u8 g, u8 b, u8 a)
{
    sClearColor.r = r;
    sClearColor.g = g;
    sClearColor.b = b;
    sClearColor.a = a;
}