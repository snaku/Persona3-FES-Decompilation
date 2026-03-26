#ifndef K_SPIPE_H
#define K_SPIPE_H

#include "Utils.h"

typedef struct KwlnTask KwlnTask;

KwlnTask* K_SPipe_Create3DDrwBeginTask(KwlnTask* draw3DTask);
KwlnTask* K_SPipe_Create3DDrwEndTask(KwlnTask* draw3DTask);

#endif