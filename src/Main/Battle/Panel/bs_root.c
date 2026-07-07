#include "Main/Battle/Panel/bs_root.h"
#include "Main/Battle/Panel/bp_tex.h"
#include "h_cdvd.h"
#include "rw/rwcore.h"

#define BSROOT_INIT_TMXCOUNT 2
#define BSROOT_INIT_SPRCOUNT 1

static void* sUnk_007ce3a8[BSROOT_INIT_SPRCOUNT]; // 007ce3a8
static RwRaster* sRasters[BSROOT_INIT_TMXCOUNT];  // 007ce3a0

// FUN_00267370
RwRaster* bsRootGetRaster(u32 id)
{
    return sRasters[id];
}