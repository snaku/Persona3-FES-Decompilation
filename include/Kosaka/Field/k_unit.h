#ifndef K_UNIT_H
#define K_UNIT_H

#include "Utils.h"
#include "rw/rwplcore.h"

#define FLDUNIT_HERO 0
#define FLDUNIT_MAX  4

typedef struct Model Model;
typedef struct ResrcModelParty ResrcModelParty;

// 448 bytes
typedef struct FldUnit
{
    RwMatrix matBeforeBtl;  // 0x00. Saved matrix before entering a battle
    u8 unkData1[0x08];
    void* unk_48;           // 0x48
    s32 unk_4c;             // 0x4c
    Model* mdl;             // 0x50
    ResrcModelParty* resrc; // 0x54
    u8 unkData2[0x150];
    u16 charId;             // 0x1a8
    u8 unkData3[0x16];
} FldUnit;

extern FldUnit gFldUnits[FLDUNIT_MAX];

#endif