#include "Kosaka/Field/k_fldrc.h"
#include "h_cdvd.h"
#include "temporary.h"

static H_Cdvd* sFldArchiveCdvd; // 007ce15c. "field/pack/f%03d_%03d.pac"

// FUN_001b0870
void K_FldRc_RequestFldArchive(s16 majorId, s16 minorId)
{
    char buffer[64];

    if (sFldArchiveCdvd == NULL)
    {
        sprintf(buffer, "field/pack/f%03d_%03d.pac", majorId, minorId);
        sFldArchiveCdvd = H_Cdvd_Request(buffer, H_CDVD_FILEARCHIVE);
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
H_Cdvd* K_FldRc_GetFldArchiveCdvd()
{
    return sFldArchiveCdvd;
}