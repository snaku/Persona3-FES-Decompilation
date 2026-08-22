#ifndef TYPE_H
#define TYPE_H

#if defined(__INTELLISENSE__) || defined(__clang__) || defined(__clang_analyzer__)
#define asm(...) ((void)0)
#endif

typedef unsigned char u8;
typedef signed char s8;

typedef unsigned short u16;
typedef signed short s16;

typedef unsigned int u32;
typedef signed int s32;

typedef unsigned long long u64;
typedef signed long long s64;

typedef unsigned int u128 __attribute__((mode(TI)));
typedef signed int s128 __attribute__((mode(TI)));

typedef float f32;
typedef double f64;

typedef s32 intptr_t;
typedef u32 uintptr_t;

typedef u32 size_t;

#define NULL ((void*)0)

// M2C placeholders
typedef s32 M2C_UNK;
#define M2C_FIELD(expr, type_ptr, offset) (*(type_ptr)((s8 *)(expr) + (offset)))

#endif // TYPE_H