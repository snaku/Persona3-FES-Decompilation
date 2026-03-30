#include "Kosaka/Field/k_field.h"
#include "kwln/kwlnTask.h"
#include "temporary.h"

static K_Field sField; // 00869f60

// FUN_001b90f0
void K_Field_Init()
{
    memset(&sField, 0, sizeof(K_Field));
}

// FUN_001b9120
K_Field* K_Field_Get()
{
    return &sField;
}

// FUN_001bab20. Get field major id by the root field task. Not really used that much, 'gMtScene' is used instead
s16 K_Field_GetMajorId(KwlnTask* fldRootTask)
{
    return ((K_FieldRoot*)fldRootTask->taskData)->majorId;
}

// FUN_001bab30. Get field minor id by the root field task. Not really used that much, 'gMtScene' is used instead
s16 K_Field_GetMinorId(KwlnTask* fldRootTask)
{
    return ((K_FieldRoot*)fldRootTask->taskData)->minorId;
}