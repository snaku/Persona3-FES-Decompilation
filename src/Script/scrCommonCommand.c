#include "Script/scrCommonCommand.h"
#include "Script/scrTraceCode.h"
#include "Kosaka/k_command.h"
#include "datCalendar.h"
#include "temporary.h"

u8 scrCommand_PUT();
u8 scrCommand_PUTSTR();

// 007b92b0
ScrCommandTable gScrCmdTable =
{
    // cmds. TODO
    {
        { NULL, 0 },
    },

    // cmdNo
    ARRAY_SIZE(gScrCmdTable.cmds)
};

// FUN_0035b090
u8 scrCommand_PUT()
{
    s32 param;

    param = scrGetIntPara(0);
    printf("PUT -> %d\n", param);

    return true;
}

// FUN_0035b0d0
u8 scrCommand_PUTSTR()
{
    char* param;

    param = scrGetStrPara(0);
    printf("PUTSTR -> %s\n", param);

    return true;
}