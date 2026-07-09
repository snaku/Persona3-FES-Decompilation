#include "Camp/h_camp.h"
#include "Kernel/Kwln/kwlnTask.h"
#include "Main/g_data.h"
#include "rw/rwplcore.h"

KwlnTask* gUnk_007cdf5c;               // 007cdf5c
KwlnTask* gCampPersonaKaniControlTask; // 007cdf58
KwlnTask* gCampPcKaniControlTask;      // 007cdf54
KwlnTask* gUnk_007cdf50;               // 007cdf50

static const char* sCourageLevelString[] =
{
    "Timid", "Ordinary", "Determined", "Though", "Fearless", "Badass"
};

static const char* sCharmLevelString[] =
{   
    "Plain", "Unpolished", "Confident", "Smooth", "Popular", "Charismatic"
};

static const char* sAcademicLevelString[] = 
{
    "Slacker", "Average", "Above Average", "Smart", "Intelligent", "Genius"
};

// FUN_0011a050
void* H_Camp_UpdateDrawTask(KwlnTask* hcampDrawTask)
{
    // TODO

    return KWLNTASK_CONTINUE;
}

// FUN_0011a710
void H_Camp_DestroyDrawTask(KwlnTask* hcampDrawTask)
{
    HCampDrawWork* work;

    work = (HCampDrawWork*)hcampDrawTask->workData;

    gCampPcKaniControlTask = NULL;
    gCampPersonaKaniControlTask = NULL;
    gUnk_007cdf50 = NULL;
    gUnk_007cdf5c = NULL;

    datSetFlag(FLG_HIDE_DATE_HUD, false);

    RwFree(work);
}

// FUN_0011a770
KwlnTask* H_Camp_CreateDrawTask(KwlnTask* parent)
{
    KwlnTask* task;
    HCampDrawWork* work;

    work = RwCalloc(1, sizeof(HCampDrawWork), rwMEMHINTDUR_GLOBAL);
    if (work == NULL)
    {
        return NULL;
    }

    task = kwlnTaskCreate(parent,
                          "H_CampDraw",
                          6335,
                          H_Camp_UpdateDrawTask,
                          H_Camp_DestroyDrawTask,
                          work);

    if (task == NULL)
    {
        return NULL;
    }

    return task;
}

// FUN_0011a810
const char* H_Camp_GetAcademicLevelString(u16 idx)
{
    return sAcademicLevelString[idx];
}

// FUN_0011a840
const char* H_Camp_GetCharmLevelString(u16 idx)
{
    return sCharmLevelString[idx];
}

// FUN_0011a870
const char* H_Camp_GetCourageLevelString(u16 idx)
{
    return sCourageLevelString[idx];
}