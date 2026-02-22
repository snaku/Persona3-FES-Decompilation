#ifndef DATUNIT_H
#define DATUNIT_H

#include "Utils.h"

#define UNIT_FLAG_ACTIVE (1 << 0) // 0x01. Not sure of this one
#define UNIT_FLAG_ENEMY  (1 << 2) // 0x04

#define UNIT_STATUS_FLAG_CHARM    (1 << 0)  // 0x01
#define UNIT_STATUS_FLAG_DISTRESS (1 << 1)  // 0x02
#define UNIT_STATUS_FLAG_DIZZY    (1 << 2)  // 0x04
#define UNIT_STATUS_FLAG_FEAR     (1 << 3)  // 0x08
#define UNIT_STATUS_FLAG_RAGE     (1 << 4)  // 0x10
#define UNIT_STATUS_FLAG_FREEZE   (1 << 5)  // 0x20
#define UNIT_STATUS_FLAG_SHOCK    (1 << 6)  // 0x40
#define UNIT_STATUS_FLAG_POISON   (1 << 7)  // 0x80
#define UNIT_STATUS_FLAG_ORGIA    (1 << 8)  // 0x100
#define UNIT_STATUS_FLAG_OVERHEAT (1 << 9)  // 0x200
#define UNIT_STATUS_FLAG_DEAD     (1 << 19) // 0x80000
#define UNIT_STATUS_FLAG_DOWN     (1 << 20) // 0x100000

// 16 bytes
typedef struct
{
    u8 level;
    u16 health;
    u16 sp;
    u32 flags;   // See 'UNIT_STATUS_FLAG_*'
    u8 aiTactic; // See enum AiTactic
} UnitStatus;

// 60 bytes
typedef struct UnitData
{
    u16 flags; // See 'UNIT_FLAG_*'
    u16 id;
    u16 id2;
    UnitStatus status;
    u8 unkData1[0x28];
} UnitData; 

#endif