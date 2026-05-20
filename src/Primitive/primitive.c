#include "Primitive/primitive.h"
#include "kwln/kwln.h"
#include "sce/eestruct.h"
#include "temporary.h"

#define PRIM_RENDERSTATE_COUNT 6

// 8 bytes
typedef struct 
{
    u32 renderState; // 0x00
    u32 val;         // 0x04
} PrimRenderState;

// 0069ce60
static const PrimRenderState sRenderStates[PRIM_RENDERSTATE_COUNT] =
{
    {rwRENDERSTATEFOGENABLE, false},
    {rwRENDERSTATEVERTEXALPHAENABLE, true}, 
    {rwRENDERSTATESHADEMODE, rwSHADEMODEGOURAUD},
    {rwRENDERSTATECULLMODE, rwCULLMODECULLNONE},
    {rwRENDERSTATEZTESTENABLE, true},
    {rwRENDERSTATEZWRITEENABLE, false}
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

static const RwV3d sSphereRotAxis = {1.0f, 0.0f, 0.0f}; // 0069cec8

// TODO: maybe 'pushRenderStates' and 'popRenderStates' inline functions

// FUN_00359110
void primLine3D(const RwV3d* startPos, const RwV3d* endPos, const RwRGBA* color, u32 saveAndRestoreRenderState)
{
    u32 i;
    const PrimRenderState* currRenderState;
    RwIm3DVertex vertices[2];
    RwMatrix identity;
    u32 savedRenderStates[PRIM_RENDERSTATE_COUNT];
    u32 j;

    if (saveAndRestoreRenderState)
    {
        for (i = 0; i < PRIM_RENDERSTATE_COUNT; i++)
        {
            currRenderState = &sRenderStates[i];

            RwRenderStateGet(currRenderState->renderState, &savedRenderStates[i]); // TODO: regs stuff match
            RwRenderStateSet(currRenderState->renderState, currRenderState->val);
        }

        RwRenderStateSet(rwRENDERSTATETEXTURERASTER, NULL);

        RpSkyRenderStateSet(rpSKYRENDERSTATEALPHA_1, (void*)SCE_GS_SET_ALPHA_1(0, 2, 0, 1, 0));
        RpSkyRenderStateSet(rpSKYRENDERSTATEATEST_1, (void*)SCE_GS_SET_TEST_1(1, 0, 128, 1, 0, 0, 1, 3));
    }

    RwMatrixSetIdentity(&identity);

    RwIm3DVertexSetPos(&vertices[0], startPos->x, startPos->y, startPos->z);
    RwIm3DVertexSetPos(&vertices[1], endPos->x, endPos->y, endPos->z);
    RwIm3DVertexSetRGBA(&vertices[0], color->r, color->g, color->b, color->a);
    RwIm3DVertexSetRGBA(&vertices[1], color->r, color->g, color->b, color->a);

    RwIm3DTransform(vertices, 2, &identity, rwIM3D_ALLOPAQUE);
    RwIm3DRenderLine(0, 1);

    if (saveAndRestoreRenderState)
    {
        for (j = 0; j < PRIM_RENDERSTATE_COUNT; j++)
        {
            currRenderState = &sRenderStates[j];

            RwRenderStateSet(currRenderState->renderState, savedRenderStates[j]); // TODO: regs stuff match
        }
    }
}

// FUN_00359380. Draw 3 lines representing the XYZ axis
void primAxisLine3D(const RwMatrix* mat, f32 length, u32 saveAndRestoreRenderState)
{
    u32 i;
    const PrimRenderState* currRenderState;
    u32 savedRenderStates[PRIM_RENDERSTATE_COUNT];
    u32* currSavedRenderState;
    u32 j;
    const RwV3d* currAxisDir;
    RwV3d finalAxisPoint;
    RwV3d axisPoint;

    if (saveAndRestoreRenderState)
    {
        for (i = 0; i < PRIM_RENDERSTATE_COUNT; i++)
        {
            currRenderState = &sRenderStates[i];

            RwRenderStateGet(currRenderState->renderState, &savedRenderStates[i]); // TODO: regs stuff match
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
        for (j = 0; j < PRIM_RENDERSTATE_COUNT; j++)
        {
            currRenderState = &sRenderStates[j];

            RwRenderStateSet(currRenderState->renderState, savedRenderStates[j]); // TODO: regs stuff match
        }
    }
}

// FUN_00359560
void primCircleLine3D(const RwV3d* center, f32 radius, const RwRGBA* color, const RwMatrix* mat, u32 saveAndRestoreRenderState)
{
    // TODO
}

// FUN_00359b40. Draw a wireframe sphere
void primSphereLine3D(const RwV3d* center, f32 radius, const RwRGBA* color, u32 saveAndRestoreRenderState)
{
    u32 i;
    const PrimRenderState* currRenderState;
    RwMatrix mat;
    u32 savedRenderStates[PRIM_RENDERSTATE_COUNT];
    u32* currSavedRenderState;
    RwV3d finalCenter;
    RwSphere rwSphere;
    RwV3d rotAxis;
    u32 j;
    f32 yOffset;
    f32 circleRadius;
    f32 angle;

    rotAxis = sSphereRotAxis;
    rwSphere.radius = radius;
    rwSphere.center.x = center->x;
    rwSphere.center.y = center->y;
    rwSphere.center.z = center->z;
    if (RwCameraFrustumTestSphere(RwCameraGetCurrentCamera(), &rwSphere) != rwSPHEREOUTSIDE)
    {
        if (saveAndRestoreRenderState)
        {
            for (i = 0; i < PRIM_RENDERSTATE_COUNT; i++)
            {
                currRenderState = &sRenderStates[i];

                RwRenderStateGet(currRenderState->renderState, &savedRenderStates[i]); // TODO: regs stuff match
                RwRenderStateSet(currRenderState->renderState, currRenderState->val);
            }

            RwRenderStateSet(rwRENDERSTATETEXTURERASTER, NULL);

            RpSkyRenderStateSet(rpSKYRENDERSTATEALPHA_1, (void*)SCE_GS_SET_ALPHA_1(0, 2, 0, 1, 0));
            RpSkyRenderStateSet(rpSKYRENDERSTATEATEST_1, (void*)SCE_GS_SET_TEST_1(1, 0, 128, 1, 0, 0, 1, 3));
        }

        mat.right.x = mat.up.y = mat.at.z = 1.0f;
        angle = 0.0f;
        mat.right.y = mat.right.z = mat.up.x = 0.0f;
        mat.up.z = mat.at.x = mat.at.y = 0.0f;
        mat.pos.x = mat.pos.y = mat.pos.z = 0.0f;
        mat.flags |= (rwMATRIXINTERNALIDENTITY | rwMATRIXTYPEORTHONORMAL);

        for (j = 0; j < 9; j++)
        {
            angle += g18deg;
            yOffset = radius * cosf(angle);
            circleRadius = radius * sinf(angle);

            finalCenter.x = center->x;
            finalCenter.y = center->y + yOffset;
            finalCenter.z = center->z;

            primCircleLine3D(&finalCenter, circleRadius, color, &mat, false);
        }

        RwMatrixRotate(&mat, &rotAxis, 90.0f, rwCOMBINEPOSTCONCAT);

        angle = 0.0f; // regswap (f21 but should be f22)
        for (j = 0; j < 9; j++)
        {
            angle += g18deg;
            yOffset = radius * cosf(angle);
            circleRadius = radius * sinf(angle);

            finalCenter.x = center->x;
            finalCenter.y = center->y + yOffset;
            finalCenter.z = center->z;

            primCircleLine3D(&finalCenter, circleRadius, color, &mat, false);
        }

        if (saveAndRestoreRenderState)
        {
            for (j = 0; j < PRIM_RENDERSTATE_COUNT; j++)
            {
                currRenderState = &sRenderStates[j];

                RwRenderStateSet(currRenderState->renderState, savedRenderStates[j]); // TODO: regs stuff match
            }
        }
    }
}

// FUN_00359e50. Draw a wireframe cylinder
void primCylinderLine3D(const RwV3d* center, f32 radius, f32 height, const RwRGBA* color, u32 saveAndRestoreRenderState)
{
    // TODO
}