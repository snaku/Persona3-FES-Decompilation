#ifndef RPRANDOM_H
#define RPRANDOM_H

#include "rw/rwplcore.h"

void RpRandomSeedMT(RwUInt32 seed);
void RpRandomSeed(RwUInt32 seed);
RwUInt32 RpRandom();

#endif