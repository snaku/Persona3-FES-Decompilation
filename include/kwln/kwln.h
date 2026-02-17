#ifndef KWLN_H
#define KWLN_H

#include "Utils.h"

typedef struct KwlnTask KwlnTask;
typedef struct RwCamera RwCamera;
typedef struct RwRGBA RwRGBA;

RwCamera* Kwln_GetMainCamera();
RwRGBA* Kwln_GetClearColor();
void Kwln_SetClearColor(u8 r, u8 g, u8 b, u8 a);

#endif