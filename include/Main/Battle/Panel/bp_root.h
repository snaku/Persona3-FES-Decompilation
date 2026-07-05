#ifndef BP_ROOT_H
#define BP_ROOT_H

#include "Utils.h"

typedef struct KwlnTask KwlnTask;

KwlnTask* bpRootCreateTasks(KwlnTask* parent);
void bpRootDestroy(KwlnTask* btlPanelTask);
void bpRoot001ff350();

#endif