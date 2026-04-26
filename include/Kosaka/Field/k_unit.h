#ifndef K_UNIT_H
#define K_UNIT_H

#include "Utils.h"

#define FLDUNIT_HERO 0
#define FLDUNIT_MAX  4

typedef struct Model Model;
typedef struct ResrcModelParty ResrcModelParty;

// 448 bytes
typedef struct FldUnit
{
    u8 unkData1[0x50];
    Model* mdl;             // 0x50
    ResrcModelParty* resrc; // 0x54
    u8 unkData2[0x168];
} FldUnit;

extern FldUnit gFldUnits[FLDUNIT_MAX];

#endif