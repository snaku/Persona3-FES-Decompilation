#include "Kosaka/k_data.h"
#include "h_cdvd.h"
#include "g_data.h"
#include "temporary.h"

K_FieldDungeonFloorData gFldDngFloorsData[500]; // 00867f60

// FUN_001b7c40. Read 'dungeonAT.bin' or 'dungeonFES.bin' and copy its content in 'gFldDngFloorsData'
void K_Data_LoadDngFloorsData(u32 scenarioMode)
{
    char buffer[128];
    H_Cdvd* cdvd;

    if (scenarioMode == SCENARIO_MODE_JOURNEY)
    {
        sprintf(buffer, "field/table/dungeonAT.bin");
    }
    else
    {
        sprintf(buffer, "field/table/dungeonFES.bin");
    }

    cdvd = H_Cdvd_Request(buffer, false);
    H_Cdvd_SyncRead(cdvd);

    if (cdvd->fileSize >= 0x2000)
    {
        P3FES_ASSERT("k_data.c", 170);
    }

    memcpy((u8*)gFldDngFloorsData, (u8*)cdvd->fileMemory, cdvd->fileSize);

    H_Cdvd_Destroy(cdvd);
}