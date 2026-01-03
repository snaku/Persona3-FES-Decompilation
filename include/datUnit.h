#ifndef DATUNIT_H
#define DATUNIT_H

#include "Utils.h"

// 10 bytes
typedef struct
{
    u8 level;
    u16 health;
    u16 sp;
    u32 flags;   // See BATTLE_FLAG_*
    u8 aiTactic; // See enum AiTactic
} UnitStatus;

// 15 bytes
typedef struct
{
    u16 flags;
    u16 id;
    u16 id2;
    UnitStatus status;
} UnitData; 

#endif