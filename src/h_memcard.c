#include "h_memcard.h"
#include "sce/libmc2.h"
#include "sce/libdbc.h"

static u_long128 sAddr[SCE_MC2_DMA_BUFFER_MAX] __attribute__((aligned(64))); // 00846b80
static SceMc2SocketParam sSocketParam; // 00846eb0

static s32 sSocketNo; // 007ce024

// FUN_0018f100
void H_Memcard_Init()
{
    sceDbcInit();
    sceMc2Init(0);

    sSocketParam.option = SCE_MC2_TYPE_PS2;
    sSocketParam.port = SCE_MC2_PORT_1;
    sSocketParam.slot = 0;

    sSocketNo = sceMc2CreateSocket(&sSocketParam, sAddr);
}