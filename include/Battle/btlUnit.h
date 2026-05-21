#ifndef BTLUNIT_H
#define BTLUNIT_H

#include "Utils.h"

typedef struct DatUnit DatUnit;

// TODO. This struct contains the pos, rot and scale (and other unknown things) of the actor
// temporary name maybe ?
typedef struct BtlUnit
{
    // data before...
    u32 unkFlag_9c;      // 0x9c
    // data inbetween...
    DatUnit* datUnit;    // 0xa2c
} BtlUnit;

#endif