#include "g_data.h"
#include "Kosaka/k_assert.h"
#include "rw/rwplcore.h"
#include "temporary.h"

// FUN_002ff340
DatUnitPlayer* datUnitCreatePlayer(u16 charId)
{
    DatUnitPlayer* unitPlayer;

    unitPlayer = RwMalloc(sizeof(DatUnitPlayer), rwMEMHINTDUR_GLOBAL);
    memset(unitPlayer, 0, sizeof(DatUnitPlayer));

    unitPlayer->base.genus = UNIT_GENUS_PLAYER;
    unitPlayer->base.count = 1;
    unitPlayer->base.unit = datGetUnit(charId);

    datUnitInit(unitPlayer->base.unit, UNIT_GENUS_PLAYER, charId);

    return unitPlayer;
}

// FUN_002ff3e0
DatUnitEnemy* datUnitCreateEnemy(u16 groupdId)
{
    // TODO

    return NULL;
}

// FUN_002ff660
void datUnitRemoveEnemy(DatUnitEnemy* enm, DatUnit* unit)
{
    u16 i;
    DatUnit* curr;

    K_ASSERT(enm->base.genus == UNIT_GENUS_ENEMY, 134);
    K_ASSERT(enm->base.count <= 6, 135);

    for (i = 0; i < 6; i++)
    {
        curr = &enm->base.unit[i];

        if (unit == curr)
        {
            curr->id = 0;
            enm->base.count--;

            break;
        }
    }

    K_ASSERT(i < 6, 147);
}

// FUN_002ff890
u32 datUnitInit(DatUnit* unit, u8 genus, u16 id)
{
    // TODO

    return true;
}