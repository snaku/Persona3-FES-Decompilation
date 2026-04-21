#include "Kosaka/k_sequence.h"
#include "Kosaka/Field/k_dungeon.h"
#include "Kosaka/Field/k_field.h"
#include "kwln/kwlnTask.h"

// FUN_001b7850
s32 K_Seq_FieldExit()
{
    if (K_Field_Get()->rootTask != NULL)
    {
        kwlnTaskDestroyWithHierarchy(K_Field_Get()->rootTask);

        K_Field_Get()->rootTask = NULL;
    }

    return 0;
}

// FUN_001b78a0
u8 K_Seq_FieldCheck()
{
    if (kwlnTaskExists(K_Field_Get()->rootTask) == true)
    {
        return false;
    }

    K_Field_Get()->rootTask = NULL;

    return true;
}

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