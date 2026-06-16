#ifndef K_FLDRC_H
#define K_FLDRC_H

#include "Utils.h"

typedef struct HCdvd HCdvd;
typedef struct KwlnTask KwlnTask;

void K_Fldrc_RequestArchives();
void K_Fldrc_DestroyArchives();
void K_Fldrc_RequestFldPac(s16 majorId, s16 minorId);
u8 K_Fldrc_IsFldPacLoaded();
HCdvd* K_Fldrc_GetFldPacCdvd();
void K_Fldrc_DestroyFldPac();
void K_Fldrc_RequestFldFpc(s16 majorId, s16 minorId);
void K_Fldrc_DestroyFldFpc();
void K_Fldrc_001b0a20(s16 majorId, s16 minorId);

KwlnTask* K_Fldrc_CreateFilterTask(KwlnTask* parent);

#endif