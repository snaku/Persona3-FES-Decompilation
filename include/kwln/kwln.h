#ifndef KWLN_H
#define KWLN_H

#include "Utils.h"
#include "Kosaka/k_assert.h"
#include "rw/rpworld.h"

typedef struct KwlnTask KwlnTask;

#define KWLN_FLAG_2DDRAW (1 << 0)  // 0x01
#define KWLN_FLAG_3DDRAW (1 << 1)  // 0x02
#define KWLN_FLAG_ERR    (1 << 30) // 0x40000000

#define DEG_TO_RAD(deg) (gPI * (deg) / 180.0f)
#define RAD_TO_DEG(rad) (gRadToDegFactor * (rad))

extern u32 gT0CountVal;
extern u8 gFogAlpha;
extern u8 gFogGreen;
extern u8 gFogBlue;
extern u8 gFogRed;
extern u32 gFogEnabled;

extern u32 gCurrWorldIdx;

extern const f32 g18deg;
extern const f32 gRadToDegFactor;
extern const f32 gPI;
extern const f32 gAspectRatio;

void kwlnMain();

void kwlnPushCommonRenderStates();
RpWorld* kwlnGetWorld(u32 worldIdx);
RpLight* kwlnGetAmbientLight();
RpLight* kwlnGetDirectionalLight();
RwCamera* kwlnGetMainCamera();
RwRGBA* kwlnGetClearColor();
void kwlnSetClearColor(u8 r, u8 g, u8 b, u8 a);
u32 kwlnGetFlags();
void kwlnSetFlags(u32 flag, u32 enabled);

inline RwCamera* kwlnCameraBeginUpdate()
{
    return RwCameraBeginUpdate(kwlnGetMainCamera());
}

inline RwCamera* kwlnCameraEndUpdate()
{
    return RwCameraEndUpdate(kwlnGetMainCamera());
}

#endif