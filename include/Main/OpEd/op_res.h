#ifndef OP_RES_H
#define OP_RES_H

#include "Utils.h"

#define OPRES_FLAG_TITLE (1 << 0) // 0x01
#define OPRES_FLAG_LOGO (1 << 1)  // 0x02

#define OPRES_TITLE_SPRCOUNT 1
#define OPRES_TITLE_TMXCOUNT (OPRES_TITLE_MAX - OPRES_TITLE_SPRCOUNT) // 14

#define OPRES_TITLE_TMXID(contentId) ((contentId) - OPRES_TITLE_SPRCOUNT)

typedef struct HCdvd HCdvd;
typedef struct RwRaster RwRaster;

typedef enum
{
    // .spr
    OPRES_TITLE_AGSTITLESPR01,

    // .tmx
    OPRES_TITLE_NEWTITLE009,
    OPRES_TITLE_NEWTITLE010,
    OPRES_TITLE_NEWTITLE011,
    OPRES_TITLE_NEWTITLE012,
    OPRES_TITLE_NEWTITLE013,
    OPRES_TITLE_NEWTITLE014,
    OPRES_TITLE_NEWTITLE015,
    OPRES_TITLE_NEWTITLE016,
    OPRES_TITLE_NEWTITLE017,
    OPRES_TITLE_NEWTITLE018,
    OPRES_TITLE_NEWTITLE019,
    OPRES_TITLE_NEWTITLE020,
    OPRES_TITLE_NEWTITLE021,
    OPRES_TITLE_NEWTITLE022,

    OPRES_TITLE_MAX
} OpResTitleContent;

typedef enum
{
    // .tmx
    OPRES_LOGO_ATLUS,
    OPRES_LOGO_CRI,

    OPRES_LOGO_MAX
} OpResLogoContent;

// 84 bytes
typedef struct OpResWork
{
    u32 requestFlags;                             // 0x00
    u32 destroyFlags;                             // 0x04
    HCdvd* titleCdvd;                             // 0x08
    RwRaster* titleRasters[OPRES_TITLE_TMXCOUNT]; // 0x0c
    void* unk_44[OPRES_TITLE_SPRCOUNT];           // 0x44
    HCdvd* logoCdvd;                              // 0x48
    RwRaster* logoRasters[OPRES_LOGO_MAX];        // 0x4c
} OpResWork;

void opResInit(OpResWork* work);
void opResUpdate();

void opResRequestTitle();
u32 opResCheckRequestTitle();
RwRaster* opResGetTitleRaster(u32 id);

void opResRequestLogo();
u32 opResCheckRequestLogo();
RwRaster* opResGetLogoRaster(u32 id);

#endif