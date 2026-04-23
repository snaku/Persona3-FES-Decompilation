/**
* This file contains functions, structs, enums and macros that have been identified,
* but i don't have enough informations to put them in their proper files yet.
*/

#ifndef TEMPORARY_H
#define TEMPORARY_H

#include "Utils.h"
#include "Battle/btlActor.h"
#include "rw/rwcore.h"

#define QUARTER_PI ((PI) / 4)

// libc
void* memcpy(void* dst, void* src, u32 size);
void* memset(void* dst, u8 value, u32 size);
int printf(const char* fmt, ...);
int sprintf(char* buffer, const char* fmt, ...);
int strcmp(const char* str1, const char* str2);
char* strcpy(char* dst, const char* src);
size_t strlen(const char* str);

float tanf(float x);


#endif