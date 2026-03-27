#include "Kosaka/k_clump.h"
#include "rw/rpusrdat.h"
#include "temporary.h"

// FUN_001a6400
s32 K_Clump_MatGetUsrDataInt(RpMaterial* material, const char* name)
{
    s32 i;
    s32 val;
    RpUserDataArray* userData;
    char* currName;

    val = 0;
    for (i = 0; i < RpMaterialGetUserDataArrayCount(material); i++)
    {
        userData = RpMaterialGetUserDataArray(material, i);
        currName = RpUserDataArrayGetName(userData);

        if (strcmp(currName, name) == 0)
        {
            if (RpUserDataArrayGetFormat(userData) == rpINTUSERDATA)
            {
                val = RpUserDataArrayGetInt(userData, 0);
                break;
            }
        }
    }

    return val;
}