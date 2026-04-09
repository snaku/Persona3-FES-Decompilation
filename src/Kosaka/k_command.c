#include "Kosaka/k_command.h"
#include "Script/scrTraceCode.h"
#include "datCalendar.h"
#include "g_data.h"

// FUN_001c2780
u8 K_Cmd_IsDateInRange()
{
    u32 startMonth;
    u32 startDay;
    u32 endMonth;
    u32 endDay;
    u8 isInRange;

    startMonth = scrGetIntPara(0);
    startDay = scrGetIntPara(1);
    endMonth = scrGetIntPara(2);
    endDay = scrGetIntPara(3);

    isInRange = clndIsDateInRange(startMonth, startDay, endMonth, endDay);
    if (isInRange)
    {
        scrSetIntReturnVal(1);
    }
    else
    {
        scrSetIntReturnVal(0);
    }

    return 1;
}