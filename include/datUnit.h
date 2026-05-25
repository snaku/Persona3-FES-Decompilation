#ifndef DATUNIT_H
#define DATUNIT_H

#include "Utils.h"

#define UNIT_FLAG_ACTIVE (1 << 0) // 0x01. Not sure of this one
#define UNIT_FLAG_ENEMY  (1 << 2) // 0x04

#define UNIT_BADSTATUS_CHARM    (1 << 0)  // 0x01
#define UNIT_BADSTATUS_DISTRESS (1 << 1)  // 0x02
#define UNIT_BADSTATUS_DIZZY    (1 << 2)  // 0x04
#define UNIT_BADSTATUS_FEAR     (1 << 3)  // 0x08
#define UNIT_BADSTATUS_RAGE     (1 << 4)  // 0x10
#define UNIT_BADSTATUS_FREEZE   (1 << 5)  // 0x20
#define UNIT_BADSTATUS_SHOCK    (1 << 6)  // 0x40
#define UNIT_BADSTATUS_POISON   (1 << 7)  // 0x80
#define UNIT_BADSTATUS_ORGIA    (1 << 8)  // 0x100
#define UNIT_BADSTATUS_OVERHEAT (1 << 9)  // 0x200
#define UNIT_BADSTATUS_DEAD     (1 << 19) // 0x80000
#define UNIT_BADSTATUS_DOWN     (1 << 20) // 0x100000

typedef enum
{
    UNIT_GENUS_PLAYER,
    UNIT_GENUS_ENEMY,

    UNIT_GENUS_MAX
} UnitGenus;

// 60 bytes
typedef struct DatUnit
{
    u16 flags;         // 0x00. See 'UNIT_FLAG_'
    u16 id;            // 0x02
    u16 id2;           // 0x04
    u8 level;          // 0x06
    u16 health;        // 0x08
    u16 sp;            // 0x0a
    u32 bad;           // 0x0c. See 'UNIT_BADSTATUS_*'
    u8 aiTactic;       // 0x10. See enum 'AiTactic'
    u8 unkData1[0x28];
} DatUnit; 

// at least 8 bytes. Not sure if this struct existed in the source code, but i'm still making it to use it in 'FldUnit' struct
typedef struct DatUnitGenusBase
{
    u16 genus;     // 0x00. See enum 'UnitGenus'
    s16 unk_02;    // 0x02
    DatUnit* unit; // 0x04
} DatUnitGenusBase;

// 12 bytes
typedef struct DatUnitPlayer
{
    DatUnitGenusBase base; // 0x00
    u8 unkData[0x04];
} DatUnitPlayer;

// 372 bytes
typedef struct DatUnitEnemy
{
    DatUnitGenusBase base; // 0x00
    u16 id;                // 0x08. Idk if it should be in 'DatUnitGenusBase', but 0x08 in 'DatUnitPlayer' is never used
    u8 unkData[0x16a];
} DatUnitEnemy;

#endif