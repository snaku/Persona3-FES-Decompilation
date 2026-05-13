#ifndef LIBCDVD_H
#define LIBCDVD_H

#include "sce/eetypes.h"

#define SCECdINIT 0x00
#define SCECdINoD 0x01
#define SCECdEXIT 0x05

#define SCECdCD  1
#define SCECdDVD 2

int sceCdInit(int init_mode);
int sceCdDiskReady(int mode);
int sceCdMmode(int media);

#endif