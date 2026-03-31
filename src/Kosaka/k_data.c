#include "Kosaka/k_data.h"
#include "Kosaka/Field/k_dungeon.h"
#include "Kosaka/k_assert.h"
#include "kwln/kwlnTask.h"
#include "h_cdvd.h"
#include "g_data.h"
#include "temporary.h"

void* gFldScrMemory; // 007ce228
u32 gFldScrSize;     // 007ce224

K_FieldDungeonFloorData gFldDngFloorsData[500]; // 00867f60

// FUN_001b7b10. Read 'field.bf' and copy its content in 'gFldScrMemory' and its size in 'gFldScrSize'
void K_Data_LoadFldMainScript()
{
    char buffer[128];
    H_Cdvd* cdvd;
    u32 scrSize;
    void* scrMemory;

    sprintf(buffer, "field/script/field.bf");

    cdvd = H_Cdvd_Request(buffer, H_CDVD_FILENORMAL);
    H_Cdvd_SyncRead(cdvd);

    // TODO: 'cdvd->fileSize' is being loaded first and i don't know why
    scrSize = cdvd->fileSize;
    scrMemory = gFldScrMemory = RW_CALLOC(1, scrSize, 0x40000);
    scrSize = gFldScrSize = cdvd->fileSize;

    memcpy(scrMemory, cdvd->fileMemory, scrSize);

    H_Cdvd_Destroy(cdvd);
}

// FUN_001b7c40. Read 'dungeonAT.bin' or 'dungeonFES.bin' and copy its content in 'gFldDngFloorsData'
void K_Data_LoadDngFloorsData(u32 scenarioMode)
{
    char buffer[128];
    H_Cdvd* cdvd;
    u32 fileSize;

    if (scenarioMode == SCENARIO_MODE_JOURNEY)
    {
        sprintf(buffer, "field/table/dungeonAT.bin");
    }
    else
    {
        sprintf(buffer, "field/table/dungeonFES.bin");
    }

    cdvd = H_Cdvd_Request(buffer, H_CDVD_FILENORMAL);
    H_Cdvd_SyncRead(cdvd);

    fileSize = cdvd->fileSize;

    K_ASSERT(fileSize < 0x2000, 170);

    fileSize = cdvd->fileSize;
    memcpy((u8*)gFldDngFloorsData, (u8*)cdvd->fileMemory, fileSize);

    H_Cdvd_Destroy(cdvd);
}