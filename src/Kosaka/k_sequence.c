#include "Kosaka/k_sequence.h"
#include "Kosaka/Field/k_dungeon.h"
#include "kwln/kwlnTask.h"

// FUN_001b7a50
void K_Seq_DungeonCall(u8 isRestored, void* seqData)
{
    SeqDungeon* seq = (SeqDungeon*)seqData;

    gDungeonTask = K_FldDungeon_CreateTask(NULL, seq->floor, seq->unk_04);
}

// FUN_001b7a90
s32 K_Seq_DungeonExit()
{
    if (gDungeonTask != NULL)
    {
        kwlnTaskDestroyWithHierarchy(gDungeonTask);
    }

    return 0;
}

// FUN_001b7ac0
u8 K_Seq_DungeonCheck()
{
    if (kwlnTaskExists(gDungeonTask) == true)
    {
        return false;
    }

    gDungeonTask = NULL;

    return true;
}