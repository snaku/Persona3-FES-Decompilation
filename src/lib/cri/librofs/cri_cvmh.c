#include "type.h"

// 0x0056ADB8
u8 cvmh_GetVerInfo(void* arg0, void* arg1) {
    u8 temp_v0;

    M2C_FIELD(arg1, u8*, 0) = (u8)M2C_FIELD(arg0, u8*, 0);
    M2C_FIELD(arg1, u8*, 1) = (u8)M2C_FIELD(arg0, u8*, 1);
    temp_v0 = M2C_FIELD(arg0, u8*, 2);
    M2C_FIELD(arg1, u8*, 2) = temp_v0;
    M2C_FIELD(arg1, u8*, 3) = (u8)M2C_FIELD(arg0, u8*, 3);
    return temp_v0;
}
