#include "Battle/btlTarget.h"
#include "temporary.h"

// FUN_002d1570
void btlTargetInit(BtlTarget* target)
{
    memset(target, 0, sizeof(BtlTarget));
}

// FUN_002d15a0
void btlTargetReset(BtlTarget* target)
{
    target->targetedCount = 0;
    target->specificId = 0;
    target->commandId = 0;
    target->unk_38 = 0;

    memset(target->unk_3e, 0, sizeof(target->unk_3e));
}