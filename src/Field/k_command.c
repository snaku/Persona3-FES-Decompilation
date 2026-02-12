#include "Field/k_command.h"
#include "Script/scrTraceCode.h"
#include "datCalendar.h"
#include "g_data.h"

// FUN_001c2780
u8 FldCmd_IsDateInRange()
{
    u32 startMonth;
    u32 startDay;
    u32 endMonth;
    u32 endDay;
    u8 isInRange;

    startMonth = Scr_GetIntParam(0);
    startDay = Scr_GetIntParam(1);
    endMonth = Scr_GetIntParam(2);
    endDay = Scr_GetIntParam(3);

    isInRange = Calendar_IsDateInRange(startMonth, startDay, endMonth, endDay);
    if (isInRange)
    {
        Scr_SetCurrScriptIntRetVal(1);
    }
    else
    {
        Scr_SetCurrScriptIntRetVal(0);
    }

    return 1;
}