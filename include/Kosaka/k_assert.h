#ifndef K_ASSERT_H
#define K_ASSERT_H

#include "Utils.h"

#define K_ASSERT(condition, line) \
    do                                  \
    {                                   \
        if (!(condition))               \
        {                               \
            K_Assert(__FILE__, (line)); \
        }                               \
    } while (0)

void K_Assert(const char* file, s32 line);
void K_Abort(const char* str, const char* file, s32 line);

#endif