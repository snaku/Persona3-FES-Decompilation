#include "Model/mdlFile.h"
#include "Model/mdlManager.h"
#include "Model/mdlFldCharIds.h"
#include "datCalc.h"
#include "datUnit.h"
#include "g_data.h"
#include "temporary.h"

#define MODEL_PATH "model/"

// FUN_0031d4f0
u8 MdlFile_IsPacMdlType(u16 type)
{
    switch (type)
    {
        case MODEL_TYPE_BTLCHAR: // fallthrough
        case MODEL_TYPE_ENEMY:   return true;
    }

    return false;
}