#ifndef KWLN_H
#define KWLN_H

#include "Utils.h"
#include "rw/rpworld.h"

typedef struct KwlnTask KwlnTask;

#define DEG_TO_RAD(deg) (gPI * (deg) / 180.0f)
#define RAD_TO_DEG(rad) ((rad) * 180.0f / gPI)

extern u32 gT0CountVal;
extern u8 gFogAlpha;
extern u8 gFogGreen;
extern u8 gFogBlue;
extern u8 gFogRed;
extern u32 gFogEnabled;

extern u32 gCurrWorldIdx;

extern const f32 gAspectRatio;
extern const f32 gPI;

void kwlnMain();

RpWorld* kwlnGetWorld(u32 worldIdx);
RpLight* kwlnGetAmbientLight();
RpLight* kwlnGetDirectionalLight();
RwCamera* kwlnGetMainCamera();
RwRGBA* kwlnGetClearColor();
void kwlnSetClearColor(u8 r, u8 g, u8 b, u8 a);

inline RwCamera* kwlnCameraBeginUpdate()
{
    return RwCameraBeginUpdate(kwlnGetMainCamera());
}

inline RwCamera* kwlnCameraEndUpdate()
{
    return RwCameraEndUpdate(kwlnGetMainCamera());
}

#endif