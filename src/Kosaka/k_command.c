#include "Kosaka/k_command.h"
#include "Kosaka/Field/k_dungeon.h"
#include "Script/scrTraceCode.h"
#include "Model/mdlManager.h"
#include "datCalendar.h"
#include "g_data.h"
#include "temporary.h"

// FUN_001c26c0
u8 K_Cmd_GET_MONTH()
{
    scrSetIntReturnVal(clndGetCurrentMonth());

    return true;
}

// FUN_001c26f0
u8 K_Cmd_GET_DAY()
{
    scrSetIntReturnVal(clndGetCurrentDay());

    return true;
}

// FUN_001c2720
u8 K_Cmd_GET_DAY_OF_WEEK()
{
    scrSetIntReturnVal(clndGetCurrentWeekDay());

    return true;
}

// FUN_001c2750
u8 K_Cmd_GET_TIME()
{
    scrSetIntReturnVal(datGetTime());

    return true;
}

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

// FUN_001c2ea0
u8 K_Cmd_GET_DUNGEON_FLOOR()
{
    scrSetIntReturnVal(K_FldDungeon_GetCurrentFloor());

    return true;
}

// FUN_001c45e0
u8 K_Cmd_CREATE_FLD_MDL()
{
    char path[64];
    char buff[64];
    s32 majorId;
    u32 minorId;
    Model* mdl;

    majorId = scrGetIntPara(0);
    minorId = scrGetIntPara(1);

    if (majorId > -1)
    {
        strcpy(path, "field/rmd/m");

        sprintf(buff, "%03d_", majorId);
        strcat(path, buff);

        sprintf(buff, "%03d.RMD", minorId);
        strcat(path, buff);
    }
    else
    {
        strcpy(path, "field/grmd/fobj");
        sprintf(buff, "%03d.RMD", minorId);
        strcat(path, buff);
    }

    mdl = mdlMngCreateMdlFromPath(MODEL_TYPE_FLD,
                                  minorId,
                                  path,
                                  MDL_READASYNC);
    scrSetIntReturnVal((s32)mdl);

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