#include "Kosaka/Field/k_field.h"
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