#include "Main/g_data.h"
#include "Battle/battle.h"
#include "Kosaka/k_assert.h"
#include "rw/rwplcore.h"
#include "temporary.h"

// FUN_002ff340
DatUnitPc* datUnitCreatePc(u16 pcId)
{
    DatUnitPc* pc;

    pc = RwMalloc(sizeof(DatUnitPc), rwMEMHINTDUR_GLOBAL);
    memset(pc, 0, sizeof(DatUnitPc));

    pc->base.genus = UNIT_GENUS_PC;
    pc->base.count = 1;
    pc->base.unit = datGetUnit(pcId);

    datUnitInit(pc->base.unit, UNIT_GENUS_PC, pcId);

    return pc;
}

// FUN_002ff3e0
DatUnitEc* datUnitCreateEc(u16 encountId)
{
    u16 i;
    u16 count;
    BtlEncountTable* encount;
    DatUnitEc* ec;
    u16 j;
    u16 k;

    count = 0; // regswap (s1 but should be s0)
    i = 0;
    encount = &gEncountTbl[encountId];
    for (; i < 5; i++)
    {
        if (encount->enmIds[i] != 0) // TODO: addu v0, v1, v0 instead of addu v0, v0, v1
        {
            count++;
        }
    }

    ec = RwMalloc(sizeof(DatUnitEc), rwMEMHINTDUR_GLOBAL);
    memset(ec, 0, sizeof(DatUnitEc));

    ec->base.genus = UNIT_GENUS_EC;
    ec->base.count = count;
    ec->encountId = encountId;
    ec->base.unit = ec->units;

    j = 0;
    for (k = 0; k < 5; k++)
    {
        encount = &gEncountTbl[encountId]; // TODO: addu v1, s1, v0 instead of addu v1, v0, s0

        if (encount->enmIds[k] != 0) // TODO: addu v0, v1, v0 instead of addu v0, v0, v1
        {
            datUnitInit(&ec->base.unit[j], UNIT_GENUS_EC, encount->enmIds[k]);

            j++;
        }
    }

    return ec;
}

// FUN_002ff660
DatUnit* datUnitEcAddEnemy(DatUnitEc* ec, u16 id)
{
    u16 i;
    DatUnit* curr;

    K_ASSERT(ec->base.genus == UNIT_GENUS_EC, 100);
    K_ASSERT(ec->base.count < 6, 101);

    for (i = 0; i < 6; i++)
    {
        curr = &ec->base.unit[i];

        if (curr->id == 0)
        {
            datUnitInit(curr, UNIT_GENUS_EC, id);
            ec->base.count++;

            break;
        }
    }

    K_ASSERT(i < 6, 117);

    return curr;
}

// FUN_002ff660
void datUnitEcRemoveEnemy(DatUnitEc* ec, DatUnit* unit)
{
    u16 i;
    DatUnit* curr;

    K_ASSERT(ec->base.genus == UNIT_GENUS_EC, 134);
    K_ASSERT(ec->base.count <= 6, 135);

    for (i = 0; i < 6; i++)
    {
        curr = &ec->base.unit[i];

        if (unit == curr)
        {
            curr->id = 0;
            ec->base.count--;

            break;
        }
    }

    K_ASSERT(i < 6, 147);
}

// FUN_002ff760
void datUnitDestroyGenus(DatUnitGenusBase* genusBase)
{
    RwFree(genusBase);
}

// FUN_002ff890
u32 datUnitInit(DatUnit* unit, u8 genus, u16 id)
{
    // TODO

    return true;
}