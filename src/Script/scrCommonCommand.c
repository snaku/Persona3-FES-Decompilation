#include "Script/scrCommonCommand.h"
#include "Script/scrTraceCode.h"
#include "Kosaka/k_command.h"
#include "Kosaka/k_assert.h"
#include "rw/rprandom.h"
#include "datCalendar.h"
#include "temporary.h"

u8 scrCommand_RAND();
u8 scrCommand_SYNC();
u8 scrCommand_WAIT();
u8 scrCommand_PUT();
u8 scrCommand_PUTSTR();
u8 scrCommand_SWITCH();
u8 scrCommand_SQRT();

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

// FUN_0035afb0
u8 scrCommand_RAND()
{
    scrSetIntReturnVal(RpRandom() % (scrGetIntPara(0) + 1));

    return true;
}

// FUN_0035b000
u8 scrCommand_SYNC()
{
    return scrGetCmdTimer() != 0;
}

// FUN_0035b030
u8 scrCommand_WAIT()
{
    u32 cmdTimer;

    if (scrGetIntPara(0) < 1)
    {
        return true;
    }

    cmdTimer = scrGetCmdTimer();

    return scrGetIntPara(0) <= cmdTimer;
}

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

// FUN_0035b110
u8 scrCommand_SWITCH()
{
    s32 caseIdx;
    s32 lblIdx;

    caseIdx = scrGetIntPara(0);
    if (caseIdx < 0)
    {
        return true;
    }

    K_ASSERT(caseIdx <= 6, 342);

    lblIdx = scrGetIntPara(caseIdx + 1);
    if (lblIdx < 0)
    {
        return true;
    }

    scrSetPC(scrGetLabelAddr(lblIdx));

    return true;
}

// FUN_0035b520
u8 scrCommand_SQRT()
{
    f32 param;

    param = scrGetFloatPara(0);

    scrSetFloatReturnVal(sqrtf(param));
    // no return
}