// TODO: fake second half of g_data.c, likely spliced by datPersona.c via inlining

#include "Main/g_data.h"
#include "Kosaka/k_assert.h"
#include "temporary.h"

static u32 sScenarioMode;     // 007cdfa4. See enum 'ScenarioMode'

// FUN_0017b170
u32 datGetTotalBtl()
{
    return gGlobalWork.totalBtl;
}

// FUN_0017c8c0
DatPersonaWork* datGetPersonaByCompendium(s32 idx)
{
    K_ASSERT(idx > 0 && idx < 256, 6177);

    if (!(gGlobalWork.compendium[idx].flags & PERSONA_FLAG_VALID))
    {
        return NULL;
    }

    return &gGlobalWork.compendium[idx];
}

// FUN_0017d7f0
void datSetScenarioMode(u32 scenario)
{
    sScenarioMode = scenario;
}

// FUN_0017d800
u32 datGetScenarioMode()
{
    return sScenarioMode;
}
