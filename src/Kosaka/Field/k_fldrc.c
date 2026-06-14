#include "Kosaka/Field/k_fldrc.h"
#include "Kosaka/Field/k_fldFilter.h"
#include "kwln/kwlnTask.h"
#include "h_cdvd.h"
#include "temporary.h"

static HCdvd* sFldArchiveCdvd; // 007ce15c. "field/pack/f%03d_%03d.pac"

// FUN_001b0870
void K_FldRc_RequestFldArchive(s16 majorId, s16 minorId)
{
    char buffer[64];

    if (sFldArchiveCdvd == NULL)
    {
        sprintf(buffer, "field/pack/f%03d_%03d.pac", majorId, minorId);
        sFldArchiveCdvd = H_Cdvd_Request(buffer, HCDVD_FILEARCHIVE);
    }
}

// FUN_001b08d0
u8 K_FldRc_IsFldArchiveLoaded()
{
    if (sFldArchiveCdvd == NULL)
    {
        return true;
    }

    return H_Cdvd_IsFileLoaded(sFldArchiveCdvd) != false;
}

// FUN_001b0910
HCdvd* K_FldRc_GetFldArchiveCdvd()
{
    return sFldArchiveCdvd;
}

// FUN_001b0a20
void K_FldRc_001b0a20(s16 majorId, s16 minorId)
{
    // TODO
}

// FUN_001b5850
void* K_FldRc_UpdateFilterTask(KwlnTask* fldFilterTask)
{
    K_FldFilter_Main();

    return KWLNTASK_CONTINUE;
}

// FUN_001b5880
void K_FldRc_DestroyFilterTask(KwlnTask* fldFilterTask)
{
    RwFree(fldFilterTask->workData);
}

// FUN_001b58b0
KwlnTask* K_FldRc_CreateFilterTask(KwlnTask* parent)
{
    FldFilterWork* work;
    KwlnTask* task;

    work = RwCalloc(1, sizeof(FldFilterWork), rwMEMHINTDUR_GLOBAL);
    if (work == NULL)
    {
        return NULL;
    }

    task = kwlnTaskCreate(parent,
                          "field filter",
                          4197,
                          K_FldRc_UpdateFilterTask,
                          K_FldRc_DestroyFilterTask,
                          work);

    work->unk_08 = 1;
    work->unk_0c = 200;

    return task;
}