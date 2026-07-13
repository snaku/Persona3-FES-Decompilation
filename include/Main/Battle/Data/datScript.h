#ifndef DATSCRIPT_H
#define DATSCRIPT_H

#include "Utils.h"

typedef struct ScrData ScrData;
typedef struct DatUnit DatUnit;

// ?? bytes
typedef struct DatScriptWork
{
    DatUnit* currUnit; // 0x00
    DatUnit* oldUnit;  // 0x04
    u8 unkData[0x50];
    // ...
} DatScriptWork;

u32 datScriptIsNotEnemy();
u32 datScript003112c0(ScrData* scr); 

#endif