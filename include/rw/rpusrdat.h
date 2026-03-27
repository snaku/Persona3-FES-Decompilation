#ifndef RPUSRDAT_H
#define RPUSRDAT_H

#include "rw/rwplcore.h"

typedef struct RpMaterial RpMaterial; // TODO: Create in 'rpworld.h'

typedef enum
{
    rpNAUSERDATAFORMAT = 0,
    rpINTUSERDATA,
    rpREALUSERDATA,
    rpSTRINGUSERDATA,
} RpUserDataFormat;

// 16 bytes
typedef struct RpUserDataArray
{
    RwChar* name;            // 0x00
    RpUserDataFormat format; // 0x04
    RwInt32 numElements;     // 0x08
    void* data;              // 0x0c
} RpUserDataArray;

RwInt32 RpMaterialAddUserDataArray(RpMaterial* material, RwChar* name, RpUserDataFormat format, RwInt32 numElements);
RwInt32 RpMaterialGetUserDataArrayCount(const RpMaterial* material);
RpUserDataArray* RpMaterialGetUserDataArray(const RpMaterial* material, RwInt32 data);

RwChar* RpUserDataArrayGetName(RpUserDataArray* userData);
RpUserDataFormat RpUserDataArrayGetFormat(RpUserDataArray* userData);
RwInt32 RpUserDataArrayGetInt(RpUserDataArray* userData, RwInt32 index);

#endif