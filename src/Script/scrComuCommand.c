#include "Script/scrComuCommand.h"
#include "Script/scrTraceCode.h"
#include "Main/g_data.h"

// FUN_0035f1b0
u32 scrComuCommand_STARTED_COMU()
{
    s32 socialLink;

    socialLink = scrGetIntPara(0);

    if (datStartedSocialLink(socialLink) == true)
    {
        scrSetIntReturnVal(true);
    }
    else
    {
        scrSetIntReturnVal(false);
    }

    return true;
}