#ifndef RTANIM_H
#define RTANIM_H

#include "rw/rwcore.h"

typedef struct RtAnimInterpolatorInfo RtAnimInterpolatorInfo; // TODO

// 24 bytes
typedef struct RtAnimAnimation
{
    RtAnimInterpolatorInfo* interpInfo; // 0x00
    RwInt32 numFrames;                  // 0x04
    RwInt32 flags;                      // 0x08
    RwReal duration;                    // 0x0c
    void* pFrames;                      // 0x10
    void* customData;                   // 0x14
} RtAnimAnimation;

typedef struct RtAnimInterpolator RtAnimInterpolator;

typedef void (*RtAnimKeyFrameApplyCallBack) (void* result, void* voidIFrame);
typedef void (*RtAnimKeyFrameBlendCallBack) (void* voidOut, void* voidIn1, void* voidIn2, RwReal alpha);
typedef void (*RtAnimKeyFrameInterpolateCallBack) (void* voidOut, void* voidIn1, void* voidIn2, RwReal time, void* customData);
typedef void (*RtAnimKeyFrameAddCallBack) (void* voidOut, void* voidIn1, void* voidIn2);
typedef RtAnimInterpolator* (*RtAnimCallBack)(RtAnimInterpolator* animInstance, void* data);

// 76 bytes
struct RtAnimInterpolator
{
    RtAnimAnimation* pCurrentAnim;                           // 0x00
    RwReal currentTime;                                      // 0x04
    void* pNextFrame;                                        // 0x08
    RtAnimCallBack pAnimCallBack;                            // 0x0c
    void* pAnimCallBackData;                                 // 0x10
    RwReal animCallBackTime;                                 // 0x14
    RtAnimCallBack pAnimLoopCallBack;                        // 0x18
    void* pAnimLoopCallBackData;                             // 0x1c
    RwInt32 maxInterpKeyFrameSize;                           // 0x20
    RwInt32 currentInterpKeyFrameSize;                       // 0x24
    RwInt32 currentAnimKeyFrameSize;                         // 0x28
    RwInt32 numNodes;                                        // 0x2c
    RwBool isSubInterpoaltor;                                // 0x30
    RwInt32 offsetInParnet;                                  // 0x34
    RtAnimInterpolator* parentAnimation;                     // 0x38
    RtAnimKeyFrameApplyCallBack keyFrameApplyCB;             // 0x3c
    RtAnimKeyFrameBlendCallBack keyFrameBlendCB;             // 0x40
    RtAnimKeyFrameInterpolateCallBack keyFrameInterpolateCB; // 0x44
    RtAnimKeyFrameAddCallBack keyFrameAddCB;                 // 0x48
};

#endif