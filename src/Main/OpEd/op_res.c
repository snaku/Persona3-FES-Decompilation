#include "Main/OpEd/op_res.h"
#include "Kosaka/k_assert.h"
#include "h_cdvd.h"

static OpResWork* sWork; // 007ce394

// FUN_00266a20
void opResRequestTitle()
{
    OpResWork* work;

    K_ASSERT(sWork != NULL, 68);

    work = sWork;

    K_ASSERT(~work->requestFlags & OPRES_FLAG_TITLE, 191);
    K_ASSERT(~work->destroyFlags & OPRES_FLAG_TITLE, 192);

    work->titleCdvd = H_Cdvd_Request("oped/op_title.bin", HCDVD_FILEARCHIVE);
    work->requestFlags |= OPRES_FLAG_TITLE;
}

// FUN_00266ae0
u32 opResCheckRequestTitle()
{
    K_ASSERT(sWork != NULL, 68);

    return sWork->requestFlags & OPRES_FLAG_TITLE;
}

// FUN_00266bf0
RwRaster* opResGetTitleRaster(u32 id)
{
    K_ASSERT(sWork != NULL, 68);

    return sWork->titleRasters[id];
}

// FUN_00266cb0
void opResRequestLogo()
{
    OpResWork* work;

    K_ASSERT(sWork != NULL, 68);
    work = sWork;

    K_ASSERT(~work->requestFlags & OPRES_FLAG_LOGO, 237);
    K_ASSERT(~work->destroyFlags & OPRES_FLAG_LOGO, 238);

    work->logoCdvd = H_Cdvd_Request("oped/op_logo.bin", HCDVD_FILEARCHIVE);
    work->requestFlags |= OPRES_FLAG_LOGO;
}

// FUN_00266d70
u32 opResCheckRequestLogo()
{
    K_ASSERT(sWork != NULL, 68);

    return sWork->requestFlags & OPRES_FLAG_LOGO;
}

// FUN_00266e50
RwRaster* opResGetLogoRaster(u32 id)
{
    K_ASSERT(sWork != NULL, 68);

    return sWork->logoRasters[id];
}