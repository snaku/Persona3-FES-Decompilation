#ifndef LIBPAD_H
#define LIBPAD_H

#include "sce/eetypes.h"

#define scePadDmaBufferMax (16)

int scePadInit(int mode);
int scePadPortOpen(int port, int slot, u_long128* addr);

#endif