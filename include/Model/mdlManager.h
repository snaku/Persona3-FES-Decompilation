#ifndef MDLMANAGER_H
#define MDLMANAGER_H

#include "Utils.h"
#include "rw/rwplcore.h"

typedef enum
{
    MODEL_TYPE_BTLCHAR = 1, // BC*.RMD    - "MODEL/PACK/" (in .pac)
    MODEL_TYPE_ENEMY,       // EM*.RMD    - "MODEL/PACK/" (in .pac)
    MODEL_TYPE_PERSONA,     // PS*.RMD    - "MODEL/PERSONA/"
    MODEL_TYPE_NPC = 5,     // N*.RMD     - "MODEL/NPC/"
    MODEL_TYPE_WEAPON = 7,  // WP*.RMD    - "MODEL/WEAPON/"
    MODEL_TYPE_ENEMYSYMBOL, // ES*.RMD    - "MODEL/SYMBOL/"
    MODEL_TYPE_FLDCHAR,     // FC_*_*.RMD - "MODEL/FIELD/"
    MODEL_TYPE_WEAPONH,     // WP*_H.RMD  - "MODEL/WEAPON/"
    MODEL_TYPE_PERSONAFCL   // FP*.RMD    - "MODEL/FACILITYP/"
} ModelType;

// 1072 bytes
typedef struct Model
{
    RwMatrix mat;      // 0x00
    u8 unkData1[0x94];
    u16 type;          // 0xd4. See enum 'ModelType'
    u16 id;            // 0xd6. Usually, ids are linear. For 'MODEL_TYPE_FLDCHAR', id is composite (see 'MDL_FLDCHAR_*' macros)
    u8 unkData[0x358];
} Model;

Model* MdlManager_InitMdl(u32 type, u32 id);
Model* MdlManager_CreateMdl(u32 type, u32 id, u32 flags);
RwMatrix* MdlManager_GetMdlMatrix(Model* mdl);

#endif