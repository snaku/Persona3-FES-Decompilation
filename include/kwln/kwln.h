#ifndef KWLN_H
#define KWLN_H

#include "Utils.h"
#include "rw/rpworld.h"

typedef struct KwlnTask KwlnTask;

extern u8 gFogAlpha;
extern u8 gFogGreen;
extern u8 gFogBlue;
extern u8 gFogRed;
extern u32 gFogEnabled;

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