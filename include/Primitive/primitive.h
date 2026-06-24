#ifndef PRIMITIVE_H
#define PRIMITIVE_H

#include "Utils.h"
#include "rw/rwcore.h"

void primQuad3D(const RwV3d* pos, const RwRGBA* col, f32 size, u32 saveAndRestoreRenderState);
void primLine3D(const RwV3d* startPos, const RwV3d* endPos, const RwRGBA* color, u32 saveAndRestoreRenderState);
void primAxisLine3D(const RwMatrix* mat, f32 length, u32 saveAndRestoreRenderState);
void primCircleLine3D(const RwV3d* center, f32 radius, const RwRGBA* color, const RwMatrix* mat, u32 saveAndRestoreRenderState);
void primSphereLine3D(const RwV3d* center, f32 radius, const RwRGBA* color, u32 saveAndRestoreRenderState);
void primCylinderLine3D(const RwV3d* center, f32 radius, f32 height, const RwRGBA* color, u32 saveAndRestoreRenderState);

#endif