#include "h_dbprt.h"

#define HDBPRT_LOG_MAXLINE 15
#define HDBPRT_LOG_MAXCHAR 256

static s8 sLogIdx;            // 007cdec4
static u32 sDrawLogEnabled;   // 007cdec0

static char sLogs[HDBPRT_LOG_MAXLINE][HDBPRT_LOG_MAXCHAR]; // 007e0a30. Strings in the log box

// FUN_00104d10
void H_Dbprt_Fmt(RwV2d pos, const char* fmt, ...)
{
    // TODO
}

// FUN_001052b0
void H_Dbprt_FmtLog(const char* fmt, ...)
{
    // TODO
}