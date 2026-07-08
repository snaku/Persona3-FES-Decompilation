#include "Kosaka/Field/k_fldFilter.h"
#include "Kernel/Kwln/kwln.h"
#include "rw/rwcore.h"
#include "Tohyama/h_cdvd.h"
#include "temporary.h"

#define FLDFILTER_FILE_SIZE 74752 // in bytes

// num of pixels in a single quad
#define FLDFILTER_QUAD_XPIXELS 80
#define FLDFILTER_QUAD_YPIXELS 64
#define FLDFILTER_GRID_WIDTH  (SCREEN_WIDTH / FLDFILTER_QUAD_XPIXELS)  // 8
#define FLDFILTER_GRID_HEIGHT (SCREEN_HEIGHT / FLDFILTER_QUAD_YPIXELS) // 7

// 256 bytes
typedef struct
{
    RwIm2DVertex vert[4]; // 0x00
} FilterQuad;

static void* sFilterFile; // 007ce298

static FilterQuad sFilterGrid[FLDFILTER_GRID_HEIGHT][FLDFILTER_GRID_WIDTH]; // 00872240

// FUN_001d4460
static void K_FldFilter_InitQuads(RwCamera* camera)
{
    // TODO
}

// FUN_001d4560
void K_FldFilter_Init()
{
    HCdvd* cdvd;

    if (sFilterFile == NULL)
    {
        sFilterFile = RwCalloc(1, FLDFILTER_FILE_SIZE, rwMEMHINTDUR_GLOBAL);
    }

    cdvd = H_Cdvd_Request("field/FILTER.FLD", HCDVD_FILENORMAL);
    H_Cdvd_ReadSync(cdvd);

    memcpy(sFilterFile, cdvd->fileMemory, FLDFILTER_FILE_SIZE);

    H_Cdvd_Destroy(cdvd);

    K_FldFilter_InitQuads(kwlnGetMainCamera());
}

// FUN_001d4610
void K_FldFilter_Main()
{
    // TODO
}