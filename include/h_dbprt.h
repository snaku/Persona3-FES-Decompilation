#ifndef H_DBPRT_H
#define H_DBPRT_H

#include "Utils.h"
#include "rw/rwcore.h"

void H_Dbprt_Fmt(RwV2d pos, const char* fmt, ...);
void H_Dbprt_FmtLog(const char* fmt, ...);

#endif