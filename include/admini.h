#ifndef ADMINI_H
#define ADMINI_H

#include "Utils.h"

typedef struct KwlnTask KwlnTask;

#define ADMINI_FLAG_CHANGING_SEQ (1 << 0)   // 0x1
#define ADMINI_FLAG_PASSED_CHECK  (1 << 1)  // 0x2. Ptr func 'adminiCheck' of current sequence returned true
#define ADMINI_FLAG_RESTORABLE    (1 << 2)  // 0x4. Can be restorable
#define ADMINI_FLAG_UNK08         (1 << 3)  // 0x8
#define ADMINI_FLAG_RESTORE_PREV  (1 << 16) // 0x10000. Restore previous sequence

#define ADMINI_RESET_FLAGS(admini, flagsToReset) ((admini)->flags &= ~(flagsToReset))
#define ADMINI_SET_FLAGS(admini, flagsToSet)     ((admini)->flags |= (flagsToSet))
#define ADMINI_SET_RESET_FLAGS(admini, flagsToReset, flagsToSet) \
        ((admini)->flags = ((admini)->flags & ~(flagsToReset)) | (flagsToSet))

typedef enum
{
    ADMINI_SEQ_NULL,
    ADMINI_SEQ_TEST,
    ADMINI_SEQ_FIELD_ROOT,
    ADMINI_SEQ_FIELD_ROOT2,
    ADMINI_SEQ_MAP,
    ADMINI_SEQ_DUNGEON,
    ADMINI_SEQ_BATTLE_BOSS,
    ADMINI_SEQ_FACILITY,
    ADMINI_SEQ_MAX,

    ADMINI_SEQ_INVALID = -1
} AdminiSeqId;

// 36 bytes
typedef struct AdminiWork
{
    u32 flags;                      // 0x00
    u32 timer;                      // 0x04. Increments every frame while 'seq' doesn't change
    s8 nowSeqId;                    // 0x08. Current task id. See enum 'AdminiSeqId'
    s8 seqIdToSet;                  // 0x09. See enum 'AdminiSeqId'
    u8 oldSeqIdx;                   // 0x0a. Idx to access 'oldSeqIds' and 'oldSeqFlags'
    u8 unk_0b;                      // 0x0b
    s8 oldSeqIds[ADMINI_SEQ_MAX];   // 0x0c. History of sequence ids
    s8 oldSeqFlags[ADMINI_SEQ_MAX]; // 0x14. History of admini flags
    void* seqData;                  // 0x1c. Current sequence data
    u8 seqDataSize;                 // 0x20. Current sequence data size in bytes
    u8 seqChangeDelay;              // 0x21. Frames until sequence transition. Set by 'adminiExit' return value + 1
    u8 unk_22;                      // 0x22
    u8 unk_23;                      // 0x23
} AdminiWork;

void adminiChangeTask(s8 seqId, void* seqData, u8 seqDataSize, u8 isNotRestorable);
void adminiForcePassedCheck();
s8 adminiGetNowSeqId();
s8 adminiGetSeqIdToSet();
KwlnTask* adminiCreateTask();

#endif