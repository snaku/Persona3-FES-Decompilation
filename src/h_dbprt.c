#include "h_dbprt.h"
#include "h_cdvd.h"
#include "temporary.h"

#define HDBPRT_LOG_MAXLINE 15
#define HDBPRT_LOG_MAXCHAR 256

// divided by 12 because a single character in the texture is 12 * 12 pixels
#define HDBPRT_GRID_WIDTH  (640 / 12)
#define HDBPRT_GRID_HEIGHT (480 / 12)

const RwV2d sLogBoxPos = {28.0f, 42.0f};     // 007cb290
const RwV2d sLogStringsPos = {36.0f, 50.0f}; // 007cb298

static RwRaster* sFontRaster;  // 007cded0
static RwImage* sFontImage;    // 007cdecc
static HDbText3D* sText3DList; // 007cdec8. Linked list of """3D""" strings
static s8 sLogLine;            // 007cdec4. Current line in the log
static u32 sDrawLogEnabled;    // 007cdec0
static char sGrid[HDBPRT_GRID_HEIGHT][HDBPRT_GRID_WIDTH];  // 007e1e30. Grids of characters wherever on the screen
static char sLogs[HDBPRT_LOG_MAXLINE][HDBPRT_LOG_MAXCHAR]; // 007e0a30. Strings in the log box

// FUN_001042e0
void H_Dbprt_Init()
{
    HCdvd* cdvd;
    RwRaster* raster;

    cdvd = H_Cdvd_Request("font/size12/f11_001.tmx", HCDVD_FILENORMAL);
    H_Cdvd_ReadSync(cdvd);

    sFontImage = RwImageRead("font/size12/f11_001.tmx");

    H_Cdvd_Destroy(cdvd);

    raster = RwRasterCreate(sFontImage->width,
                            sFontImage->height,
                            4,
                            rwRASTERTYPETEXTURE |
                            rwRASTERFORMATPAL4  |
                            rwRASTERFORMAT8888);
    sFontRaster = raster;
    RwRasterSetFromImage(raster, sFontImage);

    RwImageDestroy(sFontImage);
    sFontImage = NULL;

    H_Cdvd_001007f0();

    memset(sGrid, ' ', sizeof(sGrid));
    sText3DList = NULL;
}

// FUN_001043b0
void H_Dbprt_Flush()
{
    // TODO
}

// FUN_00104420
void H_Dbprt_Main()
{
    // TODO
}

// FUN_00104d10
void H_Dbprt_FmtAt(RwV2d pos, const char* fmt, ...)
{
    // TODO
}

// FUN_00104eb0. Forces to be in 2D (with color)
void H_Dbprt_FmtCol3D(RwV2d pos, RwRGBA col, const char* fmt, ...)
{
    // TODO
}

// FUN_00104fd0. Forces to be in 2D
void H_Dbprt_Fmt3D(RwV2d pos, const char* fmt, ...)
{
    // TODO
}

// FUN_001050e0. Forces to be in 2D (with a Z offset)
void H_Dbprt_FmtZOff3D(RwV2d pos, f32 zOffset, const char* fmt, ...)
{
    // TODO
}

// FUN_001052b0
void H_Dbprt_FmtLog(const char* fmt, ...)
{
    // TODO
}