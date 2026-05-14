#ifndef SIFDEV_H
#define SIFDEV_H

#include "sce/eetypes.h"

int sceSifInitIopHeap();

int sceSifLoadModule(char *filename, int args, char *argp);

int sceSifRebootIop(char *img);
int sceSifSyncIop();

#define IOP_IMAGE_FILE "IOPRP310.IMG"

#endif