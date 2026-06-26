#ifndef BTLVOICE_H
#define BTLVOICE_H

#include "Utils.h"

typedef struct BtlPacket BtlPacket;
typedef struct BtlAction BtlAction;

BtlPacket* btlVoice002e2be0(BtlAction* action, s32 param_2, s32 param_3, s32 param_4, s32 param_5);

#endif