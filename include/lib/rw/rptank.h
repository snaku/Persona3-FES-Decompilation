#ifndef RPTANK_H
#define RPTANK_H

#include "rw/rwplcore.h"

// 8 bytes
typedef struct RpPTankLockStruct
{
  u8* data;     // 0x00
  int stride;   // 0x04
} RpPTankLockStruct;

// 16 bytes
typedef union RwSkySplitBits128
{
    u128 field128;            // 0x00
    u32 field_64[2];         // 0x00
    RwSplitBits field_32[4]; // 0x00
} RwSkySplitBits128;

// 32 bytes
typedef struct _rpPTankSkyBufferInfo
{
    RwSkySplitBits128 callTag; // 0x00
    u32 refCnt;                // 0x10
    u32 clrCnt;                // 0x14
    u32 limit;                 // 0x18
    u32 start;                 // 0x1c
} _rpPTankSkyBufferInfo;

// 24 bytes
typedef struct _rpPTankSkyClusterInfo
{
    u32 cluster;     // 0x00
    u32 batchSize;   // 0x04
    u32 constSize;   // 0x08
    u32 batchUnpack; // 0x0c
    u32 constUnpack; // 0x10
    u32 cmd;         // 0x14
} _rpPTankSkyClusterInfo;

// 160 bytes
typedef struct _rpPTankSkyTransformInfo
{
    u32 prim;                           // 0x00
    u32 regs;                           // 0x08
    u32 batchSize;                      // 0x10
    u32 offset;                         // 0x14
    u32 numClusters;                    // 0x18
    void* vuCode[2];                    // 0x1c
    _rpPTankSkyClusterInfo clusters[5]; // 0x24
    u32 pad;                            // 0x9c
} _rpPTankSkyTransformInfo;

// 400 bytes
typedef struct RpPTankSkyData
{
    _rpPTankSkyBufferInfo buffers[2];        // 0x00
    RwSkySplitBits128 clusterTags[5];        // 0x40
    u32 clusterStrides[5];                   // 0x90
    u32 alpha;                               // 0xb8
    u32 clamp;                               // 0xc0
    u32 test;                                // 0xc8
    u32 tex1;                                // 0xd0
    s32 fastPipe;                            // 0xd8
    s32 refillDMApacket;                     // 0xdc
    s32 frameBuffering;                      // 0xe0
    s32 frameIdx;                            // 0xe4
    s32 bufferedFrame;                       // 0xe8
    u32 instFlag[2];                         // 0xec
    u8 vuStride[4];                          // 0xf4
    void* vuCode;                            // 0xf8
    _rpPTankSkyTransformInfo* transformInfo; // 0xfc
    s32 clusterConst[9];                     // 0x100
    u32 maxBatches;                          // 0x124
    u32 tagBatchSize;                        // 0x128
    u32 dataBatchSize;                       // 0x12c
    u32 tagConstSize;                        // 0x130
    u32 dataConstSize;                       // 0x134
    RwResEntry* resEntry[2];                 // 0x138
    char clusters[80];                       // 0x140
} RpPTankSkyData;

// 12 bytes
typedef struct RpPTankFormatDescriptor
{
    s32 numClusters; // 0x00
    s32 stride;      // 0x04
    s32 dataFlags;   // 0x08
} RpPTankFormatDescriptor;

// 8 bytes
typedef struct RpPTankLockStruct
{
    u8* data;   // 0x00
    s32 stride; // 0x04
} RpPTankLockStruct;

// 240 bytes
typedef struct RpPTankData
{
    void* data;                     // 0x00
    RpPTankLockStruct clusters[9];  // 0x04
    void* userData;                 // 0x4c
    RpPTankFormatDescriptor format; // 0x50
    u32 srcBlend;                   // 0x5c
    u32 dstBlend;                   // 0x60
    s32 vertexAlphaBlend;           // 0x64
    RwV2d cCenter;                  // 0x68
    RwV2d cSize;                    // 0x70
    f32 cRotate;                    // 0x78
    RwRGBA cColor;                  // 0x7c
    RwRGBA cVtxColor[4];            // 0x80
    RwTexCoords cUV[4];             // 0x90
    RwMatrixTag cMatrix;            // 0xb0
} RpPTankData;

// 16 bytes
typedef struct RpPTankCallBacks
{
    void** alloc;  // 0x00
    s32* create;   // 0x04
    s32* instance; // 0x08
    s32* render;   // 0x0c
} RpPTankCallBacks;

// 320 bytes
typedef struct RpPTankAtomicExtPrv
{
    s32 maxPCount;                   // 0x00
    s32 actPCount;                   // 0x04
    s32 isAStructure;                // 0x08
    void* rawdata;                   // 0x0c
    RpAtomic** defaultRenderCB;      // 0x10
    RpPTankCallBacks ptankCallBacks; // 0x14
    void* insSetupCB;                // 0x24
    void* insPosCB;                  // 0x28
    void* insUVCB;                   // 0x2c
    void* insColorsCB;               // 0x30
    void* insNormalsCB;              // 0x34
    void* insEndingCB;               // 0x38
    u32 lockFlags;                   // 0x3c
    u32 instFlags;                   // 0x40
    u32 platFlags;                   // 0x44
    INSERT_PADDING(0x8);             // 0x48
    RpPTankData publicData;          // 0x50
} RpPTankAtomicExtPrv;

// 24 bytes
typedef struct RpPTankSkyGlobalData
{
    RxPipeline* fastPipeline;        // 0x00
    RxPipeline* spr2dgenMatPipeline; // 0x04
    RxPipeline* spr2dgenObjPipeline; // 0x08
    RxPipeline* spr3dgenMatPipeline; // 0x0c
    RxPipeline* spr3dgenObjPipeline; // 0x10
    RxPipeline* skygenObjPipeline;   // 0x14
} RpPTankSkyGlobalData;

// 72 bytes
typedef struct RpPTANKInstanceSetupData
{
    s32 instancePositions;         // 0x00
    s32 instanceUVs;               // 0x04
    s32 instanceColors;            // 0x08
    s32 instanceNormals;           // 0x0c
    RpPTankLockStruct positionOut; // 0x10
    RpPTankLockStruct UVOut;       // 0x18
    RpPTankLockStruct colorsOut;   // 0x20
    RpPTankLockStruct normalsOut;  // 0x28
    RwV3d right;                   // 0x30
    RwV3d up;                      // 0x3c
} RpPTANKInstanceSetupData;

typedef enum RpPTankLockFlags
{
    rpPTANKLOCKWRITE = 0x40000000,
    rpPTANKLOCKREAD = 0x80000000,
} RpPTankLockFlags;

s32 RpPTankPluginAttach(void); // 0x002C1BC0
RpAtomic* RpPTankAtomicCreate(s32 maxParticleNum, u32 dataFlags, u32 platFlags); // 0x002C2BF0
RpAtomic* _rpPTankAtomicCreateCustom(s32 maxParticleNum, u32 dataFlags, u32 platFlags, RpPTankCallBacks* callbacks); // 0x002C2C50
void RpPTankAtomicDestroy(RpAtomic* ptank); // 0x002C3090
s32 RpPTankAtomicLock(RpAtomic* atomic, RpPTankLockStruct* dst, u32 dataFlags, RpPTankLockFlags lockFlag); // 0x002C30C0
RpAtomic* RpPTankAtomicUnlock(RpAtomic* atomic); // 0x002C3330
s32 _rpPTankSkySetupRenderStateRaster(RpPTankData* ptankGlobal, RwTexture* texture); // 0x002C3380
s32 _rpPTankSkySetupRenderStateAddress(RpPTankData* ptankGlobal, RwTexture* texture); // 0x002C3490
s32 _rpPTankSkySetupRenderStateBlend(RpPTankData* ptankGlobal); // 0x002C35F0
void* PTankOpen(void* object); // 0x002C37D0
void* PTankClose(void* object); // 0x002C3890
void _rpPTankSkySetData(RpAtomic* atomic, void* data); // 0x002C3C10
void _rpPTankSkyWaitForDispatch(RpAtomic* atomic); // 0x002C4E00
void _rptankscrMemSet32(void* dst, s32 size, s32 value); // 0x002C5390
void _rptankscrMemSet64(void* dst, s32 size, u64* value); // 0x002C56D0
void _rptankscrMemSet128(void* dst, s32 size, RwSkySplitBits128* value); // 0x002C59E0
void _rptankscrMemSet256(void* dst, s32 size, RwSkySplitBits128* value); // 0x002C5CB0
void _rptankscrMemCopy(void* dst, void* src, s32 size); // 0x002C5F90
void rpPTankSkyInsSetup_Spr2dGen(RpPTANKInstanceSetupData* data, RpAtomic* atomic, RpPTankData* ptankGlobal, u32 instFlags); // 0x002C64A0
void rpPTankSkyInsPos_Spr2dGen(RpPTankLockStruct* dstCluster, s32 pCount, RpPTankData* ptankGlobal); // 0x002C6B60
void rpPTankSkyInsColorPPC_Spr2dGen(RpPTankLockStruct* dstCluster, s32 pCount, RpPTankData* ptankGlobal); // 0x002C6C60
void rpPTankSkyInsColorPP_Spr2dGen(RpPTankLockStruct* dstCluster, s32 pCount, RpPTankData* ptankGlobal); // 0x002C6D40
void rpPTankSkyInsUV2C_Spr2dGen(RpPTankLockStruct* dstCluster, s32 pCount, RpPTankData* ptankGlobal); // 0x002C6E40
void rpPTankSkyInsUV2_Spr2dGen(RpPTankLockStruct* dstCluster, s32 pCount, RpPTankData* ptankGlobal); // 0x002C6F60
void rpPTankSkyInsSizePC_Spr2dGen(RpPTankLockStruct* dstCluster, s32 pCount, RpPTankData* ptankGlobal); // 0x002C7060
void rpPTankSkyInsSizePP_Spr2dGen(RpPTankLockStruct* dstCluster, s32 pCount, RpPTankData* ptankGlobal); // 0x002C7140
s32 _rpPTankSkyspr2dgenCreate(RpAtomic* atomic, s32 maxPCount); // 0x002C8170
s32 _rpPTankSkyspr2dgenCreatePipes(RpPTankSkyGlobalData* gData); // 0x002C8410
void rpPTankSkyInsSetup_Spr3dGen(RpPTANKInstanceSetupData* data, RpAtomic* atomic, RpPTankData* ptankGlobal, u32 instFlags); // 0x002C8490
s32 _rpPTankSkyspr3dgenCreate(RpAtomic* atomic, s32 maxPCount); // 0x002C9CE0
s32 _rpPTankSkyspr3dgenCreatePipes(RpPTankSkyGlobalData* gData); // 0x002C9F80
s32 _rpPTankSkyFastInstance(RpPTankData* pTankData, u32 instFlags); // 0x002CA000
RxPipeline* _rpPTankSkyCreateFastPipeline(void); // 0x002CA860
RxPipeline* rpSkyGenCreatePS2AllObjPipeline(void); // 0x002CAF70
void _rpPTankSkyInstanceSelectCB(RpAtomic* atomic); // 0x002CC140
void rpPTankSkyInsPosNCCSNR(RpPTankLockStruct* dstCluster, RwV3d* right, RwV3d* up, s32 pCount, RpPTankData* ptankGlobal); // 0x002CC4C0
void rpPTankSkyInsPosCCCSNR(RpPTankLockStruct* dstCluster, RwV3d* right, RwV3d* up, s32 pCount, RpPTankData* ptankGlobal); // 0x002CCCB0
void rpPTankSkyInsPosNCCSPR(RpPTankLockStruct* dstCluster, RwV3d* right, RwV3d* up, s32 pCount, RpPTankData* ptankGlobal); // 0x002CD560
void rpPTankSkyInsPosNCPSNR(RpPTankLockStruct* dstCluster, RwV3d* right, RwV3d* up, s32 pCount, RpPTankData* ptankGlobal); // 0x002CE6D0
void rpPTankSkyInsPosNCPSPR(RpPTankLockStruct* dstCluster, RwV3d* right, RwV3d* up, s32 pCount, RpPTankData* ptankGlobal); // 0x002CF4A0
void rpPTankSkyInsPosCCCSPR(RpPTankLockStruct* dstCluster, RwV3d* right, RwV3d* up, s32 pCount, RpPTankData* ptankGlobal); // 0x002D0870
void rpPTankSkyInsPosCCPSNR(RpPTankLockStruct* dstCluster, RwV3d* right, RwV3d* up, s32 pCount, RpPTankData* ptankGlobal); // 0x002D1C50
void rpPTankSkyInsPosCCPSPR(RpPTankLockStruct* dstCluster, RwV3d* right, RwV3d* up, s32 pCount, RpPTankData* ptankGlobal); // 0x002D2AB0
void rpPTankSkyInsPosNCPM(RpPTankLockStruct* dstCluster, s32 pCount, RpPTankData* ptankGlobal); // 0x002D3F50
void rpPTankSkyInsPosCCPM(RpPTankLockStruct* dstCluster, s32 pCount, RpPTankData* ptankGlobal); // 0x002D47F0
void rpPTankSkyInsColorPP(RpPTankLockStruct* dstCluster, s32 pCount, RpPTankData* ptankGlobal); // 0x002D50C0
void rpPTankSkyInsColorPV(RpPTankLockStruct* dstCluster, s32 pCount, RpPTankData* ptankGlobal); // 0x002D5A80
void rpPTankSkyInsColorPVC(RpPTankLockStruct* dstCluster, s32 pCount, RpPTankData* ptankGlobal); // 0x002D5BB0
void rpPTankSkyInsColorPPC(RpPTankLockStruct* dstCluster, s32 pCount, RpPTankData* ptankGlobal); // 0x002D5D00
void rpPTankSkyInsUV2(RpPTankLockStruct* dstCluster, s32 pCount, RpPTankData* ptankGlobal); // 0x002D5E10
void rpPTankSkyInsUV4(RpPTankLockStruct* dstCluster, s32 pCount, RpPTankData* ptankGlobal); // 0x002D6630
void rpPTankSkyInsUV2C(RpPTankLockStruct* dstCluster, s32 pCount, RpPTankData* ptankGlobal); // 0x002D67A0
void rpPTankSkyInsUV4C(RpPTankLockStruct* dstCluster, s32 pCount, RpPTankData* ptankGlobal); // 0x002D6940
void rpPTankSkyInsNormals(RpPTankLockStruct* dstCluster, s32 pCount, RpPTankData* ptankGlobal); // 0x002D6B00
s32 _rpPTankGENInstance(RpAtomic* atomic, RpPTankData* ptankGlobal, s32 actPCount, u32 instFlags); // 0x002D6C20
s32 _rpPTankGenCreate(RpAtomic* atomic, s32 maxPCount, u32 dataFlags); // 0x002D6E00
void _rpPTankGENKill(RpAtomic* atomic, s32 start, s32 end); // 0x002D7340
void _rpPTankGENInstanceSelectCB(RpAtomic* atomic); // 0x002D74C0
void rpPTankGENInsPosNCCSNR(RpPTankLockStruct* dstCluster, RwV3d* right, RwV3d* up, s32 pCount, RpPTankData* ptankGlobal); // 0x002D7850
void rpPTankGENInsPosCCCSNR(RpPTankLockStruct* dstCluster, RwV3d* right, RwV3d* up, s32 pCount, RpPTankData* ptankGlobal); // 0x002D7B90
void rpPTankGENInsPosNCCSPR(RpPTankLockStruct* dstCluster, RwV3d* right, RwV3d* up, s32 pCount, RpPTankData* ptankGlobal); // 0x002D7FC0
void rpPTankGENInsPosNCPSNR(RpPTankLockStruct* dstCluster, RwV3d* right, RwV3d* up, s32 pCount, RpPTankData* ptankGlobal); // 0x002D83A0
void rpPTankGENInsPosNCPSPR(RpPTankLockStruct* dstCluster, RwV3d* right, RwV3d* up, s32 pCount, RpPTankData* ptankGlobal); // 0x002D8690
void rpPTankGENInsPosCCCSPR(RpPTankLockStruct* dstCluster, RwV3d* right, RwV3d* up, s32 pCount, RpPTankData* ptankGlobal); // 0x002D8AB0
void rpPTankGENInsPosCCPSNR(RpPTankLockStruct* dstCluster, RwV3d* right, RwV3d* up, s32 pCount, RpPTankData* ptankGlobal); // 0x002D8F60
void rpPTankGENInsPosCCPSPR(RpPTankLockStruct* dstCluster, RwV3d* right, RwV3d* up, s32 pCount, RpPTankData* ptankGlobal); // 0x002D9340
void rpPTankGENInsPosNCPM(RpPTankLockStruct* dstCluster, s32 pCount, RpPTankData* ptankGlobal); // 0x002D9840
void rpPTankGENInsPosCCPM(RpPTankLockStruct* dstCluster, s32 pCount, RpPTankData* ptankGlobal); // 0x002D9B20
void rpPTankGENInsColorPP(RpPTankLockStruct* dstCluster, s32 pCount, RpPTankData* ptankGlobal); // 0x002D9DC0
void rpPTankGENInsColorPV(RpPTankLockStruct* dstCluster, s32 pCount, RpPTankData* ptankGlobal); // 0x002D9EA0
void rpPTankGENInsColorPVC(RpPTankLockStruct* dstCluster, s32 pCount, RpPTankData* ptankGlobal); // 0x002D9F90
void rpPTankGENInsColorPPC(RpPTankLockStruct* dstCluster, s32 pCount, RpPTankData* ptankGlobal); // 0x002DA080
void rpPTankGENInsUV2(RpPTankLockStruct* dstCluster, s32 pCount, RpPTankData* ptankGlobal); // 0x002DA130
void rpPTankGENInsUV4(RpPTankLockStruct* dstCluster, s32 pCount, RpPTankData* ptankGlobal); // 0x002DA240
void rpPTankGENInsUV2C(RpPTankLockStruct* dstCluster, s32 pCount, RpPTankData* ptankGlobal); // 0x002DA360
void rpPTankGENInsUV4C(RpPTankLockStruct* dstCluster, s32 pCount, RpPTankData* ptankGlobal); // 0x002DA450
void rpPTankGENInsNormals(RpPTankLockStruct* dstCluster, s32 pCount, RpPTankData* ptankGlobal); // 0x002DA560
void rpPTankGENInsSetup(RpPTANKInstanceSetupData* data, RpAtomic* atomic, RpPTankData* ptankGlobal, s32 actPCount, u32 instFlags); // 0x002DA680
void rpPTankGENInsEnding(RpAtomic* atomic); // 0x002DAB90
s32 _rpPTankGENRenderCallBack(RpAtomic* atomic, RpPTankData* ptankGlobal); // 0x002DABC0


#endif