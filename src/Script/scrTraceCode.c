#include "Script/scr.h"
#include "Script/scrTraceCode.h"

typedef u32 (*Scr_ExecOpCode)(ScrHeader* header);

// 0069d3e0
static const Scr_ExecOpCode OpCodeFuncTable[] =
{
    // TODO
};