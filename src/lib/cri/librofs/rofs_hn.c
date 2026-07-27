#include "type.h"

// 0x00566180
extern M2C_UNK RFHN_StopTrG();

// 0x00565BC0
void RFHN_CloseG(void *arg0) {
    if ((arg0 != NULL) && (M2C_FIELD(arg0, s16 *, 0x34) != 0)) {
        if (M2C_FIELD(arg0, s16 *, 0x38) == 2) {
            RFHN_StopTrG();
        }
        M2C_FIELD(arg0, s16 *, 0x36) = 0;
        M2C_FIELD(arg0, s16 *, 0x34) = 0;
    }
}
