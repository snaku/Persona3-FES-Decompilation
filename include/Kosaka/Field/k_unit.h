#ifndef K_UNIT_H
#define K_UNIT_H

#include "Utils.h"
#include "rw/rwplcore.h"

#define FLDUNIT_HERO 0
#define FLDUNIT_MAX  4

#define FLDUNIT_EN_MAX 24

typedef struct Model Model;
typedef struct ResrcModelParty ResrcModelParty;

// 8 bytes
typedef struct FldUnitMdl
{
    u16 type;   // 0x00
    u16 id;     // 0x02
    Model* mdl; // 0x04
} FldUnitMdl;

// 448 bytes
typedef struct FldUnit
{
    RwMatrix matBeforeBtl;  // 0x00. Saved matrix before entering a battle
    u8 unkData1[0x08];
    void* unk_48;           // 0x48
    FldUnitMdl unitMdl;     // 0x4c
    ResrcModelParty* resrc; // 0x54
    u8 unkData2[0x138];
    u32 scaleIdx;           // 0x190. Index for an array of different scale (RwV3d)
    u8 unkData3[0x14];
    u16 charId;             // 0x1a8
    u8 unkData4[0x16];
} FldUnit;

extern FldUnitMdl gFldUnitsMdl[FLDUNIT_MAX];
extern FldUnit gFldUnits[FLDUNIT_MAX];

extern FldUnit gEnFldUnits[FLDUNIT_EN_MAX];

void K_FldUnit_DestroyMdl(s32 unitId);

#endif