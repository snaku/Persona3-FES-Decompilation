#include "h_pad.h"
#include "temporary.h"

HPad gPads[4]; // 007e0940

static u_long128 sAddrPort1[scePadDmaBufferMax] __attribute__((aligned(64))); // 007e0840
static u_long128 sAddrPort2[scePadDmaBufferMax] __attribute__((aligned(64))); // 007e0740
static u8 sRDataPort2[32]; // 007e0720. unused
static u8 sRDataPort1[32]; // 007e0700

