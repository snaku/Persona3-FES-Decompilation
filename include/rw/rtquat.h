#ifndef RTQUAT_H
#define RTQUAT_H

#include "rw/rwplcore.h"

// 16 bytes
typedef struct RtQuat
{
    RwV3d imag;  // 0x00 
    RwReal real; // 0x0c
} RtQuat;

#define RtQuatModulusSquaredMacro(q) ((q)->real * (q)->real + RwV3dDotProductMacro(&(q)->imag, &(q)->imag))

#define RtQuatConvertToMatrix(qpQuat, mpMatrix)                     \
    do                                                              \
    {                                                               \
        RwReal rS;                                                  \
        RwV3d rV;                                                   \
        RwV3d rW;                                                   \
        RwV3d square;                                               \
        RwV3d cross;                                                \
                                                                    \
        rS = ((RwReal) 2) / RtQuatModulusSquaredMacro((qpQuat));    \
                                                                    \
        RwV3dScale(&rV, &(qpQuat)->imag, rS);                       \
        RwV3dScale(&rW, &rV, (qpQuat)->real);                       \
                                                                    \
        square.x = (qpQuat)->imag.x * rV.x;                         \
        square.y = (qpQuat)->imag.y * rV.y;                         \
        square.z = (qpQuat)->imag.z * rV.z;                         \
                                                                    \
        cross.x = (qpQuat)->imag.y * rV.z;                          \
        cross.y = (qpQuat)->imag.z * rV.x;                          \
        cross.z = (qpQuat)->imag.x * rV.y;                          \
                                                                    \
        (mpMatrix)->right.x = ((RwReal) 1) - (square.y + square.z); \
        (mpMatrix)->right.y = cross.z + rW.z;                       \
        (mpMatrix)->right.z = cross.y - rW.y;                       \
                                                                    \
        (mpMatrix)->up.x = cross.z - rW.z;                          \
        (mpMatrix)->up.y = ((RwReal) 1) - (square.z + square.x);    \
        (mpMatrix)->up.z = cross.x + rW.x;                          \
                                                                    \
        (mpMatrix)->at.x = cross.y + rW.y;                          \
        (mpMatrix)->at.y = cross.x - rW.x;                          \
        (mpMatrix)->at.z = ((RwReal) 1) - (square.x + square.y);    \
                                                                    \
        (mpMatrix)->pos.x = ((RwReal) 0);                           \
        (mpMatrix)->pos.y = ((RwReal) 0);                           \
        (mpMatrix)->pos.z = ((RwReal) 0);                           \
                                                                    \
        rwMatrixSetFlags((mpMatrix),                                \
                        (rwMATRIXTYPEORTHONORMAL  &                 \
                        ~rwMATRIXINTERNALIDENTITY) );               \
                                                                    \
    } while (0)

RwBool RtQuatConvertFromMatrix(RtQuat* quat, const RwMatrix* matrix);

#endif