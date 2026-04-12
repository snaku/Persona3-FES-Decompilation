#ifndef PRIMITIVE_H
#define PRIMITIVE_H

#include "Utils.h"
#include "rw/rwplcore.h"

void primAxisLine3D(const RwMatrix* mat, f32 scaleFactor, u32 param_3);
void primSphereLine3D(const RwV3d* center, f32 radius, const RwRGBA* color, u32 param_4);
void primCylinderLine3D(const RwV3d* center, f32 radius, f32 height, const RwRGBA* color, u32 param_5);

#endif