#include "Main/Battle/Panel/bs_root.h"
#include "Main/Battle/Panel/bp_tex.h"
#include "Tohyama/h_cdvd.h"
#include "rw/rwcore.h"

#define BSROOT_INIT_TMXCOUNT 2
#define BSROOT_INIT_SPRCOUNT 1

static void* sUnk_007ce3a8[BSROOT_INIT_SPRCOUNT]; // 007ce3a8
static RwRaster* sRasters[BSROOT_INIT_TMXCOUNT];  // 007ce3a0

// FUN_00267260
void bsRootInit()
{
    HCdvd* cdvd;
    s32 i;
    void* file;
    u32 fileSize;

    cdvd = H_Cdvd_Request("battle/panel/bs_init.bin", HCDVD_FILENORMAL); // BUG: should be 'HCDVD_FILEARCHIVE'
    H_Cdvd_ReadSync(cdvd);

    for (i = 0; i < BSROOT_INIT_MAX; i++)
    {
        file = H_Cdvd_ArchiveGetFile(cdvd, i, &fileSize);

        switch (i)
        {
            case BSROOT_INIT_PCADVANTAGE:
                sRasters[i] = bpTexCreateTmxRaster(file);
                break;
            case BSROOT_INIT_ECADVANTAGE:
                sRasters[i] = bpTexCreateTmxRaster(file);
                break;
            
            case BSROOT_INIT_RUSH:
                sUnk_007ce3a8[BSROOT_INIT_RUSH] = bpTex0021c9f0(file);
                break;
        }
    }

    H_Cdvd_Destroy(cdvd);
}

// FUN_00267370
RwRaster* bsRootGetRaster(u32 id)
{
    return sRasters[id];
}