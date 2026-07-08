#include "Main/OpEd/op_res.h"
#include "Main/Battle/Panel/bp_tex.h"
#include "Kosaka/k_assert.h"
#include "Tohyama/h_cdvd.h"

static OpResWork* sWork; // 007ce394

// FUN_00266670
void opResInit(OpResWork* work)
{
    work->requestFlags = 0;
    work->destroyFlags = 0;

    sWork = work;
}

// FUN_00266710
void opResUpdate()
{
    OpResWork* work;
    s32 i;
    void* file;
    u32 fileSize;

    K_ASSERT(sWork != NULL, 68);
    work = sWork;

    if (work->requestFlags & OPRES_FLAG_TITLE &&
        H_Cdvd_IsFileLoaded(work->titleCdvd))
    {
        for (i = 0; i < OPRES_TITLE_MAX; i++)
        {
            file = H_Cdvd_ArchiveGetFile(work->titleCdvd, i, &fileSize);

            switch (i)
            {
                case OPRES_TITLE_AGSTITLESPR01:
                    work->unk_44[OPRES_TITLE_AGSTITLESPR01] = bpTex0021c9f0(file);
                    break;

                case OPRES_TITLE_NEWTITLE009:
                    work->titleRasters[OPRES_TITLE_TMXID(OPRES_TITLE_NEWTITLE009)] = bpTexCreateTmxRaster(file);
                    break;
                case OPRES_TITLE_NEWTITLE010:
                    work->titleRasters[OPRES_TITLE_TMXID(OPRES_TITLE_NEWTITLE010)] = bpTexCreateTmxRaster(file);
                    break;
                case OPRES_TITLE_NEWTITLE011:
                    work->titleRasters[OPRES_TITLE_TMXID(OPRES_TITLE_NEWTITLE011)] = bpTexCreateTmxRaster(file);
                    break;
                case OPRES_TITLE_NEWTITLE012:
                    work->titleRasters[OPRES_TITLE_TMXID(OPRES_TITLE_NEWTITLE012)] = bpTexCreateTmxRaster(file);
                    break;
                case OPRES_TITLE_NEWTITLE013:
                    work->titleRasters[OPRES_TITLE_TMXID(OPRES_TITLE_NEWTITLE013)] = bpTexCreateTmxRaster(file);
                    break;
                case OPRES_TITLE_NEWTITLE014:
                    work->titleRasters[OPRES_TITLE_TMXID(OPRES_TITLE_NEWTITLE014)] = bpTexCreateTmxRaster(file);
                    break;
                case OPRES_TITLE_NEWTITLE015:
                    work->titleRasters[OPRES_TITLE_TMXID(OPRES_TITLE_NEWTITLE015)] = bpTexCreateTmxRaster(file);
                    break;
                case OPRES_TITLE_NEWTITLE016:
                    work->titleRasters[OPRES_TITLE_TMXID(OPRES_TITLE_NEWTITLE016)] = bpTexCreateTmxRaster(file);
                    break;
                case OPRES_TITLE_NEWTITLE017:
                    work->titleRasters[OPRES_TITLE_TMXID(OPRES_TITLE_NEWTITLE017)] = bpTexCreateTmxRaster(file);
                    break;
                case OPRES_TITLE_NEWTITLE018:
                    work->titleRasters[OPRES_TITLE_TMXID(OPRES_TITLE_NEWTITLE018)] = bpTexCreateTmxRaster(file);
                    break;
                case OPRES_TITLE_NEWTITLE019:
                    work->titleRasters[OPRES_TITLE_TMXID(OPRES_TITLE_NEWTITLE019)] = bpTexCreateTmxRaster(file);
                    break;
                case OPRES_TITLE_NEWTITLE020:
                    work->titleRasters[OPRES_TITLE_TMXID(OPRES_TITLE_NEWTITLE020)] = bpTexCreateTmxRaster(file);
                    break;
                case OPRES_TITLE_NEWTITLE021:
                    work->titleRasters[OPRES_TITLE_TMXID(OPRES_TITLE_NEWTITLE021)] = bpTexCreateTmxRaster(file);
                    break;
                case OPRES_TITLE_NEWTITLE022:
                    work->titleRasters[OPRES_TITLE_TMXID(OPRES_TITLE_NEWTITLE022)] = bpTexCreateTmxRaster(file);
                    break;
            }
        }

        work->destroyFlags |= OPRES_FLAG_TITLE;
        H_Cdvd_Destroy(work->titleCdvd);
        work->requestFlags &= ~OPRES_FLAG_TITLE;
    }

    if (work->requestFlags & OPRES_FLAG_LOGO &&
        H_Cdvd_IsFileLoaded(work->logoCdvd))
    {
        for (i = 0; i < OPRES_LOGO_MAX; i++)
        {
            file = H_Cdvd_ArchiveGetFile(work->logoCdvd, i, &fileSize);

            switch (i)
            {
                case OPRES_LOGO_ATLUS:
                    work->logoRasters[OPRES_LOGO_ATLUS] = bpTexCreateTmxRaster(file);
                    break;
                case OPRES_LOGO_CRI:
                    work->logoRasters[OPRES_LOGO_CRI] = bpTexCreateTmxRaster(file);
                    break;
            }
        }

        work->destroyFlags |= OPRES_FLAG_LOGO;
        H_Cdvd_Destroy(work->logoCdvd);
        work->requestFlags &= ~OPRES_FLAG_LOGO;
    }
}

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