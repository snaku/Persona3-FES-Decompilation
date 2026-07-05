#include "Graphics/Model/mdlFile.h"
#include "Graphics/Model/mdlManager.h"
#include "Graphics/Model/mdlFldCharIds.h"
#include "Main/g_data.h"
#include "Main/Battle/Data/datCalc.h"
#include "Main/Battle/Data/datUnit.h"
#include "temporary.h"

#define MODEL_PATH "model/"

// FUN_0031d4f0
u8 mdlFileIsTypePac(u16 type)
{
    switch (type)
    {
        case MODEL_TYPE_BTLCHAR: // fallthrough
        case MODEL_TYPE_ENEMY:   return true;
    }

    return false;
}