#include "Kosaka/k_command.h"
#include "Script/scrTraceCode.h"
#include "Model/mdlManager.h"
#include "datCalendar.h"
#include "g_data.h"

// FUN_001c2780
u8 K_Cmd_DATE_IN_RANGE()
{
    u32 startMonth;
    u32 startDay;
    u32 endMonth;
    u32 endDay;

    startMonth = scrGetIntPara(0);
    startDay = scrGetIntPara(1);
    endMonth = scrGetIntPara(2);
    endDay = scrGetIntPara(3);

    if (clndIsDateInRange(startMonth, startDay, endMonth, endDay))
    {
        scrSetIntReturnVal(1);
    }
    else
    {
        scrSetIntReturnVal(0);
    }

    return true;
}

// FUN_001c4a00
u8 K_Cmd_CREATE_MDL()
{
    s32 type;
    s32 id;
    Model* mdl;

    type = scrGetIntPara(0);
    id = scrGetIntPara(1);

    mdl = mdlMngCreateMdlAndResolvePath(type, id, MDL_READASYNC);

    scrSetIntReturnVal((s32)mdl);

    return true;
}