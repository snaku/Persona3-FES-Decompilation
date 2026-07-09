#include "Main/Battle/Panel/bp_res.h"
#include "Main/g_data.h"
#include "Kosaka/k_assert.h"
#include "Tohyama/h_cdvd.h"

static BpResWork* sWork; // 007ce304

// FUN_0021b940
void bpResRequestBpAll()
{
    BpResWork* work;
    s32 i;
    s32 j;
    s32* unk_2c;

    K_ASSERT(sWork != NULL, 89);
    work = sWork;

    if (datGetScenarioMode() != SCENARIO_MODE_JOURNEY)
    {
        if (datGetFlag(752))
        {
            work->bpAllCdvd = H_Cdvd_Request("snd_benc/panel/AGS_bp_all.bin", HCDVD_FILEARCHIVE);
        }
        else
        {
            work->bpAllCdvd = H_Cdvd_Request("snd_benc/panel/AGS2_bp_all.bin", HCDVD_FILEARCHIVE);
        }
    }
    else
    {
        work->bpAllCdvd = H_Cdvd_Request("snd_benc/panel/bp_all.bin", HCDVD_FILEARCHIVE);
    }

    work->partyIdx = 0;
    for (i = 0; i < 3; i++)
    {
        if (datGetPartyId(i) != PC_NONE)
        {
            work->partyIds[work->partyIdx] = datGetPartyId(i);
            work->partyIdx++;
        }
    }

    for (j = 0; j < work->partyIdx; j++)
    {
        unk_2c = &work->unk_2c[j];
        *unk_2c = 0;
    }

    work->requestFlags |= BPRES_FLAG_BPALL;
}

// FUN_0021bab0
u32 bpResCheckRequestBpAll()
{
    K_ASSERT(sWork != NULL, 89);

    return sWork->requestFlags & BPRES_FLAG_BPALL;
}