#ifndef K_FLDRC_H
#define K_FLDRC_H

#include "Utils.h"

typedef struct HCdvd HCdvd;

void K_FldRc_RequestFldArchive(s16 majorId, s16 minorId);
u8 K_FldRc_IsFldArchiveLoaded();
HCdvd* K_FldRc_GetFldArchiveCdvd();

#endif