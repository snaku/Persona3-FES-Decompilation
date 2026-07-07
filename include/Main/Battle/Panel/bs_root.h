#ifndef BS_ROOT_H
#define BS_ROOT_H

#include "Utils.h"

typedef struct RwRaster RwRaster;

typedef enum
{
    // .tmx
    BSROOT_INIT_PCADVANTAGE,
    BSROOT_INIT_ECADVANTAGE,

    // .spr
    BSROOT_INIT_RUSH,

    BSROOT_INIT_MAX
} BsRootInitContent;

RwRaster* bsRootGetRaster(u32 id);

#endif