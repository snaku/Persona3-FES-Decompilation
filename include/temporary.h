/**
* This file contains functions, structs, enums and macros that have been identified,
* but i don't have enough informations to put them in their proper files yet.
*/

#ifndef TEMPORARY_H
#define TEMPORARY_H

#include "Utils.h"
#include "Battle/btlActor.h"
#include "rw/rwcore.h"

extern const f32 PI; // 007cae58

#define QUARTER_PI ((PI) / 4)
#define DEG_TO_RAD(deg) (PI * (deg) / 180.0f)
#define RAD_TO_DEG(rad) ((rad) * 180.0f / PI)

#define scePadDmaBufferMax (16) // libpad.h

typedef unsigned int u_long128 __attribute__ ((mode (TI))); // eetypes.h

// libc
void* memcpy(void* dst, void* src, u32 size);
void* memset(void* dst, u8 value, u32 size);
void sprintf(char* buffer, const char* fmt, ...);
s32 strcmp(const char* str1, const char* str2);
char* strcpy(char* dst, const char* src);
size_t strlen(const char* str);

// sce
// libpad.h
int scePadInit(int mode);
int scePadPortOpen(int port, int slot, u_long128* addr);

#endif