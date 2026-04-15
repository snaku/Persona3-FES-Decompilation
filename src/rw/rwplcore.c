#include "rw/rwplcore.h"

// 00960070
RwGlobals rwGlobals;

// FUN_004c2cc0
RwBool RwEngineGetMatrixTolerances(RwMatrixTolerance* const tolerance)
{
    // TODO

    return true;
}

// FUN_004c2d20
RwMatrix* RwMatrixOptimize(RwMatrix* matrix, const RwMatrixTolerance* tolerance)
{
    // TODO

    return NULL;
}

// FUN_004c2f10
RwMatrix* RwMatrixUpdate(RwMatrix* matrix)
{
    // TODO

    return NULL;
}

// FUN_004c2f30
RwMatrix* RwMatrixMultiply(RwMatrix* matrixOut, const RwMatrix* matrixIn1, const RwMatrix* matrixIn2)
{
    RwMatrixMultiplyVUMacro(matrixOut, matrixIn1, matrixIn2);

    return matrixOut;
}

// FUN_004c31b0
RwMatrix* RwMatrixRotate(RwMatrix* matrix, const RwV3d* axis, RwReal angle, RwOpCombineType combineOp)
{
    // TODO

    return matrix;
}

// FUN_004c35d0
RwMatrix* RwMatrixTranslate(RwMatrix* matrix, const RwV3d* translation, RwOpCombineType combineOp)
{
    // TODO

    return matrix;
}

// FUN_004c69f0
RwReal RwV3dNormalize(RwV3d* out, const RwV3d* in)
{
    // TODO

    return 0.0f;
}

// FUN_004c6ac0
RwReal RwV3dLength(const RwV3d* in)
{
    // TODO

    return 0.0f;
}

// FUN_004c6af0
RwReal RwV2dLength(const RwV2d* in)
{
    // TODO

    return 0.0f;
}

// FUN_004ca510
RwUInt32 RwEngineGetVersion()
{
    return RW_LIB_VERSION;
}

// FUN_004ca850
RwBool RwEngineInit(const RwMemoryFunctions* memFuncs, RwUInt32 flags, RwUInt32 resArenaSize)
{
    // TODO

    return true;
}