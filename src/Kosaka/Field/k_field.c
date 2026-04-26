#include "Kosaka/Field/k_field.h"
#include "kwln/kwlnTask.h"
#include "temporary.h"

static Field sField; // 00869f60

// FUN_001b90f0
void K_Field_Init()
{
    memset(&sField, 0, sizeof(Field));
}

// FUN_001b9120
Field* K_Field_Get()
{
    return &sField;
}

// FUN_001ba880
void K_Field_SetShouldShutdown(KwlnTask* fldRootTask, u32 shouldShutdown)
{
    FldRootWork* work;

    work = (FldRootWork*)fldRootTask->workData;
    printf("shutdown field proc\n");

    work->shouldShutdown = shouldShutdown;
}

// FUN_001bab20. Get field major id by the root field task. Not really used that much, 'gMtScene' is used instead
s16 K_Field_GetMajorId(KwlnTask* fldRootTask)
{
    return ((FldRootWork*)fldRootTask->workData)->majorId;
}

// FUN_001bab30. Get field minor id by the root field task. Not really used that much, 'gMtScene' is used instead
s16 K_Field_GetMinorId(KwlnTask* fldRootTask)
{
    return ((FldRootWork*)fldRootTask->workData)->minorId;
}