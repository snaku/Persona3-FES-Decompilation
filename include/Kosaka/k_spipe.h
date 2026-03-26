#ifndef K_SPIPE_H
#define K_SPIPE_H

#include "Utils.h"

typedef struct KwlnTask KwlnTask;

KwlnTask* FldSPipe_Create3DDrwBeginTask(KwlnTask* draw3DTask);
KwlnTask* FldSPipe_Create3DDrwEndTask(KwlnTask* draw3DTask);

#endif