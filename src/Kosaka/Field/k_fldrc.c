#include "Kosaka/Field/k_fldrc.h"
#include "Kosaka/Field/k_fldFilter.h"
#include "Kosaka/Field/k_field.h"
#include "Kernel/Kwln/kwlnTask.h"
#include "h_cdvd.h"
#include "temporary.h"

static HCdvd* sFldFpcCdvd; // 007ce160. "field/pack/f%03d_%03d.fpc"
static HCdvd* sFldPacCdvd; // 007ce15c. "field/pack/f%03d_%03d.pac"

// FUN_001b0710
void K_Fldrc_RequestArchives()
{
    s16 major;
    s16 minor;

    if (K_Field_Get()->rootTask != NULL)
    {
        major = K_Field_GetMajorId(K_Field_Get()->rootTask);
        minor = K_Field_GetMinorId(K_Field_Get()->rootTask);
        K_Fldrc_RequestFldPac(major, minor);

        major = K_Field_GetMajorId(K_Field_Get()->rootTask);
        minor = K_Field_GetMinorId(K_Field_Get()->rootTask);
        K_Fldrc_RequestFldFpc(major, minor);
    }
}

// FUN_001b0840
void K_Fldrc_DestroyArchives()
{
    K_Fldrc_DestroyFldPac();
    K_Fldrc_DestroyFldFpc();
}

// FUN_001b0870
void K_Fldrc_RequestFldPac(s16 majorId, s16 minorId)
{
    char buffer[64];

    if (sFldPacCdvd == NULL)
    {
        sprintf(buffer, "field/pack/f%03d_%03d.pac", majorId, minorId);
        sFldPacCdvd = H_Cdvd_Request(buffer, HCDVD_FILEARCHIVE);
    }
}

// FUN_001b08d0
u8 K_Fldrc_IsFldPacLoaded()
{
    if (sFldPacCdvd == NULL)
    {
        return true;
    }

    return H_Cdvd_IsFileLoaded(sFldPacCdvd) != false;
}

// FUN_001b0910
HCdvd* K_Fldrc_GetFldPacCdvd()
{
    return sFldPacCdvd;
}

// FUN_001b0920
void K_Fldrc_DestroyFldPac()
{
    if (sFldPacCdvd != NULL)
    {
        H_Cdvd_Destroy(sFldPacCdvd);
        sFldPacCdvd = NULL;
    }
}

// FUN_001b0950
void K_Fldrc_RequestFldFpc(s16 majorId, s16 minorId)
{
    char buffer[64];

    if (sFldFpcCdvd == NULL)
    {
        sprintf(buffer, "field/pack/f%03d_%03d.fpc", majorId, minorId);
        sFldFpcCdvd = H_Cdvd_Request(buffer, HCDVD_FILEARCHIVE);
    }
}

// FUN_001b09f0
void K_Fldrc_DestroyFldFpc()
{
    if (sFldFpcCdvd != NULL)
    {
        H_Cdvd_Destroy(sFldFpcCdvd);
        sFldFpcCdvd = NULL;
    }
}

// FUN_001b0a20
void K_Fldrc_001b0a20(s16 majorId, s16 minorId)
{
    // TODO
}

// FUN_001b10f0
u32 K_Fldrc_Init()
{
    // TODO

    return false;
}

// FUN_001b5850
void* K_Fldrc_UpdateFilterTask(KwlnTask* fldFilterTask)
{
    K_FldFilter_Main();

    return KWLNTASK_CONTINUE;
}

// FUN_001b5880
void K_Fldrc_DestroyFilterTask(KwlnTask* fldFilterTask)
{
    RwFree(fldFilterTask->workData);
}

// FUN_001b58b0
KwlnTask* K_Fldrc_CreateFilterTask(KwlnTask* parent)
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
                          K_Fldrc_UpdateFilterTask,
                          K_Fldrc_DestroyFilterTask,
                          work);

    work->unk_08 = 1;
    work->unk_0c = 200;

    return task;
}