#include "type.h"

// 0x007b2808
extern M2C_UNK (*D_007b2808)();

// 0x0056A698
M2C_UNK (*dcfExecServer(void))() {
    M2C_UNK (*var_v0)();

    var_v0 = (M2C_UNK (*)()) D_007b2808;
    if (var_v0 != NULL) {
        var_v0 = (M2C_UNK (*)()) M2C_FIELD(var_v0, M2C_UNK (**)(), 0);
        if (var_v0 != NULL) {
            var_v0 = M2C_FIELD(var_v0, M2C_UNK *(*)(), 0)();
        }
    }
    return var_v0;
}