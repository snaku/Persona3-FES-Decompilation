#include "rw/rpusrdat.h"

// FUN_0048ee70
RwInt32 RpMaterialAddUserDataArray(RpMaterial* material, RwChar* name, RpUserDataFormat format, RwInt32 numElements)
{
    // TODO

    return 0;
}

// FUN_0048ee80
RwInt32 RpMaterialGetUserDataArrayCount(const RpMaterial* material)
{
    // TODO

    return 0;  
}

// FUN_0048eed0
RpUserDataArray* RpMaterialGetUserDataArray(const RpMaterial* material, RwInt32 data)
{
    // TODO

    return NULL;
}

// FUN_0048ef10
RwChar* RpUserDataArrayGetName(RpUserDataArray* userData)
{
    return userData->name;
}

// FUN_0048ef20
RpUserDataFormat RpUserDataArrayGetFormat(RpUserDataArray* userData)
{
    return userData->format;
}

// FUN_0048ef40
RwInt32 RpUserDataArrayGetInt(RpUserDataArray* userData, RwInt32 index)
{
    // TODO

    return 0;
}