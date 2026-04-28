#include "Primitive/primitive.h"
#include "sce/eestruct.h"

#define PRIM_RENDERSTATE_NO ARRAY_SIZE(sRenderStates)

// 8 bytes
typedef struct 
{
    u32 renderState; // 0x00
    u32 val;         // 0x04
} PrimRenderState;

// 0069ce60
static const PrimRenderState sRenderStates[6] =
{
    {rwRENDERSTATEFOGENABLE, false}, {12, 1}, {7, 2},
    {20, 1}, {6, 1}, {8, 0}
};

// 0069ce90
static const RwV3d sAxisDirs[3] =
{
    {1.0f, 0.0f, 0.0f}, // X
    {0.0f, 1.0f, 0.0f}, // Y
    {0.0f, 0.0f, 1.0f}  // Z
};

// 0069ceb8
static const RwRGBA sAxisColors[3] =
{
    {255, 0, 0, 255}, // X (red)
    {0, 255, 0, 255}, // Y (green)
    {0, 0, 255, 255}  // Z (blue)
};

// FUN_00359110
void primLine3D(const RwV3d* startPos, const RwV3d* endPos, const RwRGBA* color, u32 saveAndRestoreRenderState)
{
    // TODO
}

// FUN_00359380. Draw 3 lines representing the XYZ axis
void primAxisLine3D(const RwMatrix* mat, f32 length, u32 saveAndRestoreRenderState)
{
    u32 i;
    const PrimRenderState* currRenderState;
    u32 savedRenderStates[PRIM_RENDERSTATE_NO];
    u32* currSavedRenderState;
    u32 j;
    const RwV3d* currAxisDir;
    RwV3d finalAxisPoint;
    RwV3d axisPoint;

    if (saveAndRestoreRenderState)
    {
        for (i = 0; i < PRIM_RENDERSTATE_NO; i++)
        {
            currRenderState = &sRenderStates[i];
            currSavedRenderState = &savedRenderStates[i];

            // TODO: load a0 before a1
            RwRenderStateGet(currRenderState->renderState, currSavedRenderState);
            RwRenderStateSet(currRenderState->renderState, currRenderState->val);
        }

        RwRenderStateSet(rwRENDERSTATETEXTURERASTER, NULL);

        RpSkyRenderStateSet(rpSKYRENDERSTATEALPHA_1, (void*)SCE_GS_SET_ALPHA_1(0, 2, 0, 1, 0));
        RpSkyRenderStateSet(rpSKYRENDERSTATEATEST_1, (void*)SCE_GS_SET_TEST_1(1, 0, 128, 1, 0, 0, 1, 3));
    }

    for (j = 0; j < 3; j++)
    {
        currAxisDir = &sAxisDirs[j];

        axisPoint.x = length * currAxisDir->x;
        axisPoint.y = length * currAxisDir->y;
        axisPoint.z = length * currAxisDir->z;

        RwV3dTransformPoint(&finalAxisPoint, &axisPoint, mat);

        primLine3D(&mat->pos, &finalAxisPoint, &sAxisColors[j], false);
    }

    if (saveAndRestoreRenderState)
    {
        for (j = 0; j < PRIM_RENDERSTATE_NO; j++)
        {
            currRenderState = &sRenderStates[j];
            currSavedRenderState = &savedRenderStates[j];
            
            // TODO: lw a1, 0x60(v0) instead of lw a1, 0x0(v0)
            RwRenderStateSet(currRenderState->renderState, *currSavedRenderState);
        }
    }
}

// FUN_00359b40. Draw a wireframe sphere
void primSphereLine3D(const RwV3d* center, f32 radius, const RwRGBA* color, u32 saveAndRestoreRenderState)
{
    // TODO
}

// FUN_00359e50. Draw a wireframe cylinder
void primCylinderLine3D(const RwV3d* center, f32 radius, f32 height, const RwRGBA* color, u32 saveAndRestoreRenderState)
{
    // TODO
}