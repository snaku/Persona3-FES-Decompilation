#ifndef UTILS_H
#define UTILS_H

#include "type.h"

#define true  1
#define false 0

#define ARRAY_SIZE(arr) sizeof(arr) / sizeof(arr[0])

#ifndef INSERT_PADDING
#define GLUE2(a, b) a##b
#define GLUE(a, b) GLUE2(a, b)
#define INSERT_PADDING(n) u8 GLUE(__pad, __LINE__)[n]
#endif

#endif