#ifndef H_CAMP_H
#define H_CAMP_H

#include "Utils.h"

typedef struct KwlnTask KwlnTask;

// 72 bytes
typedef struct HCampDrawWork
{
    u8 unkData[0x48];
} HCampDrawWork;

KwlnTask* H_Camp_CreateDrawTask(KwlnTask* parent);

const char* H_Camp_GetAcademicLevelString(u16 idx);
const char* H_Camp_GetCharmLevelString(u16 idx);
const char* H_Camp_GetCourageLevelString(u16 idx);

#endif