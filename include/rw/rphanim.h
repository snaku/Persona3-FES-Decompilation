#ifndef RPHANIM_H
#define RPHANIM_H

#include "rw/rwcore.h"

typedef struct RtAnimInterpolator RtAnimInterpolator; // TODO: Not in this file. Create struct in 'rtanim.h'

typedef struct RpHAnimNodeInfo RpHAnimNodeInfo; // TODO

typedef struct RpHAnimHierarchy RpHAnimHierarchy;

// 36 bytes
struct RpHAnimHierarchy
{
    RwInt32 flags;                     // 0x00
    RwInt32 numNodes;                  // 0x04
    RwMatrix* pMatrixArray;            // 0x08
    void* pMatrixArrayUnaligned;       // 0x0c
    RpHAnimNodeInfo* pNodeInfo;        // 0x10
    RwFrame* parentFrame;              // 0x14
    RpHAnimHierarchy* parentHierarchy; // 0x18
    RwInt32 rootParentOffset;          // 0x1c
    RtAnimInterpolator* currentAnim;   // 0x20
};

#endif