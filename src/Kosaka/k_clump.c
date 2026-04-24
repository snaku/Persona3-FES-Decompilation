#include "Kosaka/k_clump.h"
#include "rw/rpusrdat.h"
#include "temporary.h"

// FUN_001a6400
s32 K_Clump_MatUsrDataGetInt(const RpMaterial* material, const char* name)
{
    s32 i;
    s32 val;
    RpUserDataArray* usrData;
    char* currName;

    val = 0;
    for (i = 0; i < RpMaterialGetUserDataArrayCount(material); i++)
    {
        usrData = RpMaterialGetUserDataArray(material, i);
        currName = RpUserDataArrayGetName(usrData);

        if (strcmp(currName, name) == 0 &&
           (RpUserDataArrayGetFormat(usrData) == rpINTUSERDATA))
        {
            val = RpUserDataArrayGetInt(usrData, 0);
            break;
        }
    }

    return val;
}

// FUN_001a64f0
u32 K_Clump_MatUsrDataHasData(const RpMaterial* material, const char* name)
{
    s32 i;
    s32 hasData;
    RpUserDataArray* usrData;
    char* currName;

    hasData = false;
    for (i = 0; i < RpMaterialGetUserDataArrayCount(material); i++)
    {
        usrData = RpMaterialGetUserDataArray(material, i);
        RpUserDataArrayGetName(usrData); // ?

        currName = RpUserDataArrayGetName(usrData);

        if (strcmp(currName, name) == 0)
        {
            hasData = true;
            break;
        }
    }

    return hasData;
}