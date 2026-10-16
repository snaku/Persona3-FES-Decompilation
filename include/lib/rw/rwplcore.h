#ifndef RWPLCORE_H
#define RWPLCORE_H

#include "Utils.h"
#include "sce/eetypes.h"

// RENDERWARE TYPES
typedef int RwFixed;
typedef int RwInt32;
typedef unsigned int RwUInt32;
typedef short RwInt16;
typedef unsigned short RwUInt16;
typedef unsigned char RwUInt8;
typedef signed char RwInt8;
typedef char RwChar;
typedef long RwInt64;
typedef unsigned long RwUInt64;
typedef float RwReal;
typedef RwInt32 RwBool;

// persona 3 uses renderware 3.7.0.2
#define RW_LIB_VERSION 0x37002

// pack RGBA components into an unsigned int (ARGB)
#define PACK_RWRGBA(r,g,b,a) ((RwUInt32)(((a) << 24) | ((r) << 16) | ((g) << 8) | (b)))

// macros to call 'RwGlobals' func ptr
// memFuncs
#define RwMalloc(size, hint)          rwGlobals.memFuncs.RwMalloc((size), (hint))
#define RwFree(ptr)                      rwGlobals.memFuncs.RwFree((ptr))
#define RwRealloc(ptr, newSize, hint) rwGlobals.memFuncs.RwRealloc((ptr), (newSize), (hint))
#define RwCalloc(count, size, hint)   rwGlobals.memFuncs.RwCalloc((count), (size), (hint))

// device
#define RwRenderStateSet(state, val) rwGlobals.device.setRenderState((state), (void*)(val))
#define RwRenderStateGet(state, val) rwGlobals.device.getRenderState((state), (void*)(val))

// std func
#define RWSTDFUNC(type) (rwGlobals.stdFunc[(type)])

// 4 bytes. Values from 0 to 255
typedef struct RwRGBA
{
    RwUInt8 r;
    RwUInt8 g;
    RwUInt8 b;
    RwUInt8 a;
} RwRGBA;

// 16 bytes. Values from 0.0f to 1.0f
typedef struct RwRGBAReal
{
    RwReal r;
    RwReal g;
    RwReal b;
    RwReal a;
} RwRGBAReal;

// 8 bytes
typedef struct RwV2d
{
    RwReal x; // 0x00
    RwReal y; // 0x04
} RwV2d;

// 12 bytes
typedef struct RwV3d
{
    RwReal x; // 0x00
    RwReal y; // 0x04
    RwReal z; // 0x08
} RwV3d;

#define RwV3dScale(o, a, s)      \
    do                                \
    {                                 \
        (o)->x = (((a)->x) * ( (s))); \
        (o)->y = (((a)->y) * ( (s))); \
        (o)->z = (((a)->z) * ( (s))); \
    } while (0)

#define RwV3dDotProductMacro(a, b)  \
    ((((((((a)->x) * ((b)->x)))   + \
        ((((a)->y) * ((b)->y))))) + \
        ((((a)->z) * ((b)->z)))))

// 16 bytes
typedef struct RwV4dTag
{
    RwReal x; // 0x00
    RwReal y; // 0x04
    RwReal z; // 0x08
    RwReal w; // 0x0c
} RwV4d;

// 16 bytes
typedef struct
{
    RwInt32 x; // 0x00
    RwInt32 y; // 0x04
    RwInt32 w; // 0x08
    RwInt32 h; // 0x0c
} RwRect;

// 16 bytes
typedef struct
{
    RwV3d center;  // 0x00
    RwReal radius; // 0x0c
} RwSphere;

typedef enum
{
    rwMATRIXTYPENORMAL = 0x00000001,
    rwMATRIXTYPEORTHOGONAL = 0x00000002,
    rwMATRIXTYPEORTHONORMAL = 0x00000003,
    rwMATRIXTYPEMASK = 0x00000003
} RwMatrixType;

typedef enum
{
    rwMATRIXINTERNALIDENTITY = 0x00020000
} RwMatrixFlag;

// 64 bytes
typedef struct RwMatrixTag
{
    RwV3d right;    // 0x00
    RwUInt32 flags; // 0x0c

    RwV3d up;       // 0x10
    RwUInt32 pad1;  // 0x1c

    RwV3d at;       // 0x20
    RwUInt32 pad2;  // 0x2c
    
    RwV3d pos;      // 0x30
    RwUInt32 pad3;  // 0x3c
} RwMatrix;

// 12 bytes
typedef struct RwMatrixTolerance
{
    RwReal normal;     // 0x00
    RwReal orthogonal; // 0x04
    RwReal identity;   // 0x08
} RwMatrixTolerance;

typedef enum
{
    rwCOMBINEREPLACE = 0,
    rwCOMBINEPRECONCAT = 1,
    rwCOMBINEPOSTCONCAT = 2,
    rwOPCOMBINETYPEFORCEENUMSIZEINT = 2147483647,
} RwOpCombineType;

#define rwMatrixSetFlags(m, flagsbit) ((m)->flags = (flagsbit))
#define rwMatrixGetFlags(m)           ((m)->flags)

#define RwMatrixSetIdentity(m)                                  \
do                                                              \
{                                                               \
    (m)->right.x = (m)->up.y    = (m)->at.z  = (RwReal)((1.0)); \
    (m)->right.y = (m)->right.z = (m)->up.x  = (RwReal)((0.0)); \
    (m)->up.z    = (m)->at.x    = (m)->at.y  = (RwReal)((0.0)); \
    (m)->pos.x   = (m)->pos.y   = (m)->pos.z = (RwReal)((0.0)); \
    rwMatrixSetFlags((m),                                       \
                     rwMatrixGetFlags(m) |                      \
                     (rwMATRIXINTERNALIDENTITY |                \
                      rwMATRIXTYPEORTHONORMAL));                \
} while(0)

#define RwMatrixMultiplyVUMacro(_matrix, _matrixIn1, _matrixIn2)    \
do                                                                  \
{                                                                   \
    int __tmp1, __tmp2;                                             \
                                                                    \
    asm __volatile__ (".set noreorder ;                             \
        lqc2        vf1,  0x00(%2) ;                                \
        lqc2        vf2,  0x10(%2) ;                                \
        lqc2        vf3,  0x20(%2) ;                                \
        lqc2        vf4,  0x30(%2) ;                                \
        lwu         %0,   0x0C(%2) ;                                \
        lqc2        vf5,  0x00(%3) ;                                \
        lqc2        vf6,  0x10(%3) ;                                \
        lqc2        vf7,  0x20(%3) ;                                \
        lqc2        vf8,  0x30(%3) ;                                \
        lwu         %1,   0x0C(%3) ;                                \
        vmulax.xyz  ACC,  vf5, vf1 ;                                \
        vmadday.xyz ACC,  vf6, vf1 ;                                \
        vmaddz.xyz  vf9,  vf7, vf1 ;                                \
        vmulax.xyz  ACC,  vf5, vf2 ;                                \
        vmadday.xyz ACC,  vf6, vf2 ;                                \
        vmaddz.xyz  vf10, vf7, vf2 ;                                \
        vmulax.xyz  ACC,  vf5, vf3 ;                                \
        vmadday.xyz ACC,  vf6, vf3 ;                                \
        vmaddz.xyz  vf11, vf7, vf3 ;                                \
        vmulax.xyz  ACC,  vf5, vf4 ;                                \
        vmadday.xyz ACC,  vf6, vf4 ;                                \
        vmaddaz.xyz ACC,  vf7, vf4 ;                                \
        vmaddw.xyz  vf12, vf8, vf0 ;                                \
        and         %1, %1, %0     ;                                \
        sqc2        vf9,  0x00(%4) ;                                \
        sqc2        vf10, 0x10(%4) ;                                \
        sqc2        vf11, 0x20(%4) ;                                \
        sqc2        vf12, 0x30(%4) ;                                \
        sw          %1, 0x0C(%4)   ;                                \
        .set reorder "                                              \
         : "=r&" (__tmp1), "=r&" (__tmp2) : "r" (_matrixIn1),       \
           "r" (_matrixIn2), "r" (_matrix) : "cc",  "memory");      \
} while(0)

typedef struct RwLLLink RwLLLink;

// 8 bytes
struct RwLLLink
{
    RwLLLink* next; // 0x00
    RwLLLink* prev; // 0x04
};

// 8 bytes
typedef struct RwLinkList
{
    RwLLLink link; // 0x00
} RwLinkList;

// 8 bytes
typedef struct RwObject
{
    RwUInt8 type;         // 0x00
    RwUInt8 subType;      // 0x01
    RwUInt8 flags;        // 0x02
    RwUInt8 privateFlags; // 0x03
    void* parent;         // 0x04
} RwObject;

typedef struct RwStream RwStream; // TODO


// 64 bytes
typedef struct RwSky2DVertexFields
{
    RwV3d          scrVertex;   // 0x00
    RwReal         camVertex_z; // 0x0c
    RwReal         u;           // 0x10
    RwReal         v;           // 0x14
    RwReal         recipZ;      // 0x18
    RwReal         pad1;        // 0x1c
    RwRGBAReal     color;       // 0x20
    RwV3d          objNormal;   // 0x30
    RwReal         pad2;        // 0x3c
} RwSky2DVertexFields;

// 64 bytes
typedef union
{
    RwSky2DVertexFields els;
    u_long128 qWords[4];
} RwSky2DVertexAlignementOverlay;

// 64 bytes
typedef struct RwSky2DVertex
{
    RwSky2DVertexAlignementOverlay u; // 0x00
} RwSky2DVertex;

typedef RwSky2DVertex RwIm2DVertex;

#define RwIm2DGetNearScreenZ() (rwGlobals.device.zBufferNear)
#define RwIm2DRenderPrimitive(_primType, _vertices, _numVertices) (rwGlobals.device.fpIm2DRenderPrimitive(_primType, _vertices, _numVertices))


typedef enum
{
    rwRENDERSTATENARENDERSTATE = 0,
    rwRENDERSTATETEXTURERASTER = 1,
    rwRENDERSTATETEXTUREADDRESS = 2,
    rwRENDERSTATETEXTUREADDRESSU = 3,
    rwRENDERSTATETEXTUREADDRESSV = 4,
    rwRENDERSTATETEXTUREPERSPECTIVE = 5,
    rwRENDERSTATEZTESTENABLE = 6,            // true or false
    rwRENDERSTATESHADEMODE = 7,              // See enum 'RwShadeMode'
    rwRENDERSTATEZWRITEENABLE = 8,           // true or false
    rwRENDERSTATETEXTUREFILTER = 9,          // See enum 'RwTextureFilterMode'
    rwRENDERSTATESRCBLEND = 10,              // See enum 'RwBlendFunction'
    rwRENDERSTATEDESTBLEND = 11,             // See enum 'RwBlendFunction'
    rwRENDERSTATEVERTEXALPHAENABLE = 12,     // true or false
    rwRENDERSTATEBORDERCOLOR = 13,
    rwRENDERSTATEFOGENABLE = 14,
    rwRENDERSTATEFOGCOLOR = 15,
    rwRENDERSTATEFOGTYPE = 16,               // See enum 'RwFogType'
    rwRENDERSTATEFOGDENSITY = 17,
    rwRENDERSTATECULLMODE = 20,              // See enum 'RwCullMode'
    rwRENDERSTATESTENCILENABLE = 21,
    rwRENDERSTATESTENCILFAIL = 22,
    rwRENDERSTATESTENCILZFAIL = 23,
    rwRENDERSTATESTENCILPASS = 24,
    rwRENDERSTATESTENCILFUNCTION = 25,
    rwRENDERSTATESTENCILFUNCTIONREF = 26,
    rwRENDERSTATESTENCILFUNCTIONMASK = 27,
    rwRENDERSTATESTENCILFUNCTIONWRITEMASK = 28,
    rwRENDERSTATEALPHATESTFUNCTION = 29,
    rwRENDERSTATEALPHATESTFUNCTIONREF = 30,
    rwRENDERSTATEFORCEENUMSIZEINT = 2147483647,
} RwRenderState;

typedef enum
{
    rwSHADEMODENASHADEMODE = 0,
    rwSHADEMODEFLAT = 1,
    rwSHADEMODEGOURAUD = 2,
    rwSHADEMODEFORCEENUMSIZEINT = 2147483647,
} RwShadeMode;

typedef enum
{
    rwBLENDNABLEND = 0,
    rwBLENDZERO = 1,
    rwBLENDONE = 2,
    rwBLENDSRCCOLOR = 3,
    rwBLENDINVSRCCOLOR = 4,
    rwBLENDSRCALPHA = 5,
    rwBLENDINVSRCALPHA = 6,
    rwBLENDDESTALPHA = 7,
    rwBLENDINVDESTALPHA = 8,
    rwBLENDDESTCOLOR = 9,
    rwBLENDINVDESTCOLOR = 10,
    rwBLENDSRCALPHASAT = 11,
    rwBLENDFUNCTIONFORCEENUMSIZEINT = 2147483647,
} RwBlendFunction;

typedef enum
{
    rwFILTERNAFILTERMODE = 0,
    rwFILTERNEAREST = 1,
    rwFILTERLINEAR = 2,
    rwFILTERMIPNEAREST = 3,
    rwFILTERMIPLINEAR = 4,
    rwFILTERLINEARMIPNEAREST = 5,
    rwFILTERLINEARMIPLINEAR = 6,
    rwTEXTUREFILTERMODEFORCEENUMSIZEINT = 2147483647,
} RwTextureFilterMode;

typedef enum
{
    rwFOGTYPENAFOGTYPE = 0,
    rwFOGTYPELINEAR = 1,
    rwFOGTYPEEXPONENTIAL = 2,
    rwFOGTYPEEXPONENTIAL2 = 3,
    rwFOGTYPEFORCEENUMSIZEINT = 2147483647,
} RwFogType;

typedef enum
{
    rwCULLMODENACULLMODE = 0,
    rwCULLMODECULLNONE = 1,
    rwCULLMODECULLBACK = 2,
    rwCULLMODECULLFRONT = 3,
    rwCULLMODEFORCEENUMSIZEINT = 2147483647,
} RwCullMode;

typedef enum
{
    rwSTANDARDCAMERAENDUPDATE = 10,
    rwSTANDARDCAMERACLEAR = 21,
    rwSTANDARDMAX = 29
} RwStdFunc;

typedef enum
{
    rwPRIMTYPENAPRIMTYPE = 0,
    rwPRIMTYPELINELIST = 1,
    rwPRIMTYPEPOLYLINE = 2,
    rwPRIMTYPETRILIST = 3,
    rwPRIMTYPETRISTRIP = 4,
    rwPRIMTYPETRIFAN = 5,
    rwPRIMTYPEPOINTLIST = 6,
    rwPRIMITIVETYPEFORCEENUMSIZEINT = 2147483647,
} RwPrimitiveType;

typedef RwBool (*RwStandardFunc)(void* out, void* inOut, RwInt32 nI);

typedef RwBool (*RwSystemFunc)(RwInt32 nOption, void* pOut, void* pInOut, RwInt32 nIn);

// See enmu 'RwRenderState'
typedef RwBool (*RwRenderStateSetFunc)(RwRenderState renderState, void* val);
typedef RwBool (*RwRenderStateGetFunc)(RwRenderState renderState, void* val);

typedef RwBool (*RwIm2DRenderPrimitiveFunction)(RwPrimitiveType primType, RwIm2DVertex* vertices, RwInt32 numVertices);

// 56 bytes
typedef struct RwDevice
{
    RwReal gammaCorrection;              // 0x00
    RwSystemFunc fpSystem;               // 0x04
    RwReal zBufferNear;                  // 0x08
    RwReal zBufferFar;                   // 0x0c
    RwRenderStateSetFunc setRenderState; // 0x10
    RwRenderStateGetFunc getRenderState; // 0x14                 
    void* fpIm2DRenderLine;                              // 0x18
    void* fpIm2DRenderTriangle;                          // 0x1c
    RwIm2DRenderPrimitiveFunction fpIm2DRenderPrimitive; // 0x20
    void* fpIm2DRenderIndexedPrimitive;                  // 0x24
    void* fpIm3DRenderLine;                              // 0x28
    void* fpIm3DRenderTriangle;                          // 0x2c
    void* fpIm3DRenderPrimitive;                         // 0x30
    void* fpIm3DRenderIndexedPrimitive;                  // 0x34
} RwDevice;

typedef enum
{
    rwMEMHINTDUR_NADURATION = 0x00000000,
    rwMEMHINTDUR_FUNCTION   = 0x00010000,
    rwMEMHINTDUR_FRAME      = 0x00020000,
    rwMEMHINTDUR_EVENT      = 0x00030000,
    rwMEMHINTDUR_GLOBAL     = 0x00040000,
    rwMEMHINTDUR_MASK       = 0x00FF0000
} RwMemoryHintDuration;

// 16 bytes
typedef struct RwMemoryFunctions
{
    void* (*RwMalloc)(RwUInt32 size, RwUInt32 hint);
    void  (*RwFree)(void* ptr);
    void* (*RwRealloc)(void* ptr, RwUInt32 newSize, RwUInt32 hint);
    void* (*RwCalloc)(RwUInt32 elemCount, RwUInt32 elemSize, RwUInt32 hint);
} RwMemoryFunctions;

// 300 bytes
typedef struct
{
    void* currCamera;                      // 0x00
    void* currWorld;                       // 0x04
    u8 unkData1[0x08];
    RwDevice device;                       // 0x10
    RwStandardFunc stdFunc[rwSTANDARDMAX]; // 0x48
    u8 unkData2[0x4c];
    RwMemoryFunctions memFuncs;            // 0x108
    u8 unkData3[0x10];
    RwUInt32 resArenaSize;                 // 0x128
} RwGlobals;

extern RwGlobals rwGlobals; // not sure where to place this

RwBool RwEngineGetMatrixTolerances(RwMatrixTolerance* const tolerance);
RwMatrix* RwMatrixOptimize(RwMatrix* matrix, const RwMatrixTolerance* tolerance);
RwMatrix* RwMatrixUpdate(RwMatrix* matrix);
RwMatrix* RwMatrixMultiply(RwMatrix* matrixOut, const RwMatrix* matrixIn1, const RwMatrix* matrixIn2);
RwMatrix* RwMatrixRotate(RwMatrix* matrix, const RwV3d* axis, RwReal angle, RwOpCombineType combineOp);
RwMatrix* RwMatrixScale(RwMatrix* matrix, const RwV3d* scale, RwOpCombineType combineOp);
RwMatrix* RwMatrixTranslate(RwMatrix* matrix, const RwV3d* translation, RwOpCombineType combineOp);

RwReal RwV3dNormalize(RwV3d* out, const RwV3d* in);
RwReal RwV3dLength(const RwV3d* in);
RwReal RwV2dLength(const RwV2d* in);
RwReal RwV2dNormalize(RwV2d* out, const RwV2d* in);
RwV3d* RwV3dTransformPoint(RwV3d* pointOut, const RwV3d* pointIn, const RwMatrix* matrix);

RwUInt32 RwEngineGetVersion();
RwBool RwEngineInit(const RwMemoryFunctions* memFuncs, RwUInt32 flags, RwUInt32 resArenaSize);

#endif