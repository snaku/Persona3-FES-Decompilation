#include "rw/rwplcore.h"

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

// FUN_004c33d0
RwMatrix* RwMatrixScale(RwMatrix* matrix, const RwV3d* scale, RwOpCombineType combineOp)
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
