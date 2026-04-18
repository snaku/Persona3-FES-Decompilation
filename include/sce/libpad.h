#ifndef LIBPAD_H
#define LIBPAD_H

#include "sce/eetypes.h"

#ifndef SCE_PADLup

#define SCE_PADLup     (1 << 12)
#define SCE_PADLdown   (1 << 14)
#define SCE_PADLleft   (1 << 15)
#define SCE_PADLright  (1 << 13)
#define SCE_PADRup     (1 << 4)
#define SCE_PADRdown   (1 << 6)
#define SCE_PADRleft   (1 << 7)
#define SCE_PADRright  (1 << 5)
#define SCE_PADi       (1 << 9)
#define SCE_PADj       (1 << 10)
#define SCE_PADk       (1 << 8)
#define SCE_PADl       (1 << 3)
#define SCE_PADm       (1 << 1)
#define SCE_PADn       (1 << 2)
#define SCE_PADo       (1 << 0)
#define SCE_PADh       (1 << 11)
#define SCE_PADL1      SCE_PADn
#define SCE_PADL2      SCE_PADo
#define SCE_PADR1      SCE_PADl
#define SCE_PADR2      SCE_PADm
#define SCE_PADstart   SCE_PADh
#define SCE_PADselect  SCE_PADk

#endif

#define scePadDmaBufferMax (16)

int scePadInit(int mode);
int scePadPortOpen(int port, int slot, u_long128* addr);

#endif