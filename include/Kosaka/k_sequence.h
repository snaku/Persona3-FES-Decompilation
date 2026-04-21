#ifndef K_SEQUENCE_H
#define K_SEQUENCE_H

#include "Utils.h"

// 8 bytes
typedef struct DungeonSeq
{
    u32 floor;  // 0x00
    u32 unk_04; // 0x04
} SeqDungeon;

s32 K_Seq_FieldExit();
u8 K_Seq_FieldCheck();

void K_Seq_DungeonCall(u8 isRestored, void* seqData);
s32 K_Seq_DungeonExit();
u8 K_Seq_DungeonCheck();

#endif