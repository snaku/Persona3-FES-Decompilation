#include "Kosaka/Field/k_fldrc.h"
#include "h_cdvd.h"
#include "temporary.h"

static H_Cdvd* gFldArchiveCdvd; // 007ce15c. "field/pack/f%03d_%03d.pac"

// FUN_001b0870
void K_FldRc_RequestFldArchive(s16 majorId, s16 minorId)
{
    char buffer[64];

    if (gFldArchiveCdvd == NULL)
    {
        sprintf(buffer, "field/pack/f%03d_%03d.pac", majorId, minorId);
        gFldArchiveCdvd = H_Cdvd_Request(buffer, H_CDVD_FILEARCHIVE);
    }
}