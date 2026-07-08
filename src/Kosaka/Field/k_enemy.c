#include "Kosaka/Field/k_enemy.h"
#include "Main/g_data.h"
#include "Tohyama/h_cdvd.h"
#include "temporary.h"

// FUN_001d4360
HCdvd* K_FldEnemy_RequestTable()
{
    char buffer[128];

    if (datGetScenarioMode() == SCENARIO_MODE_JOURNEY)
    {
        sprintf(buffer, "field/table/enemy.bin");
    }
    else
    {
        sprintf(buffer, "field/table/enemy_aegis.bin");
    }

    if (H_Cdvd_FileExists(buffer))
    {
        return H_Cdvd_Request(buffer, HCDVD_FILENORMAL);
    }
}