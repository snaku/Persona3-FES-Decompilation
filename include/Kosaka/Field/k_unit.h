#ifndef K_UNIT_H
#define K_UNIT_H

#include "Utils.h"
#include "rw/rwplcore.h"

#define FLDUNIT_PC_HERO 0
#define FLDUNIT_PC_MAX  4

#define FLDUNIT_EC_MAX 24

typedef struct HCdvd HCdvd;
typedef struct Model Model;
typedef struct ResrcModelChar ResrcModelChar;
typedef struct DatUnitGenusBase DatUnitGenusBase;
typedef struct BtlEncountTable BtlEncountTable;

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
    RwMatrix matBeforeBtl;       // 0x00. Saved matrix before entering a battle
    u8 unkData1[0x08];
    DatUnitGenusBase* genusBase; // 0x48. Either 'DatUnitPc' or 'DatUnitEc'
    BtlEncountTable* encount;    // 0x4c
    Model* mdl;                  // 0x50
    ResrcModelChar* resrc;       // 0x54
    s32 unk_58;                  // 0x58
    u8 unkData2[0xfc];
    RwV3d spawnPos;              // 0x158
    s32 unk_164;                 // 0x164
    void* unk_168;               // 0x168
    u8 unkData3[0x18];
    s32 unk_184;                 // 0x184
    s32 unk_188;                 // 0x188
    s32 unk_18c;                 // 0x18c
    u32 scaleIdx;                // 0x190. Index for an array of different scale (RwV3d)
    s16 xGrid;                   // 0x194
    s16 zGrid;                   // 0x196
    u8 unkData4[0x10];
    u16 charId;                  // 0x1a8
    u8 unkData5[0x06];
    HCdvd* scrCdvd;              // 0x1b0
    u8 unkData6[0x0c];
} FldUnit;

extern FldUnitMdl gFldUnitsPcMdl[FLDUNIT_PC_MAX];
extern FldUnit gFldUnitsPc[FLDUNIT_PC_MAX];

extern FldUnit gFldUnitsEc[FLDUNIT_EC_MAX];;

void K_FldUnit_DestroyPcMdl(s32 unitId);
FldUnit* K_FldUnit_FindFreePc();

FldUnit* K_FldUnit_CreateReaper(u32 unused, const RwV3d* spawnPos);

#endif