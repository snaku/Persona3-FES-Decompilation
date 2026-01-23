#include "Camp/h_camp.h"


// TODO

static const char* courageLevelString[] =
{
    "Timid", "Ordinary", "Determined", "Though", "Fearless", "Badass"
};

static const char* charmLevelString[] =
{   
    "Plain", "Unpolished", "Confident", "Smooth", "Popular", "Charismatic"
};

static const char* academicLevelString[] = 
{
    "Slacker", "Average", "Above Average", "Smart", "Intelligent", "Genius"
};

// FUN_0011a810
const char* h_camp_getAcademicLevelString(u16 idx)
{
    return academicLevelString[idx];
}

// FUN_0011a840
const char* h_camp_getCharmLevelString(u16 idx)
{
    return charmLevelString[idx];
}

// FUN_0011a870
const char* h_camp_getCourageLevelString(u16 idx)
{
    return courageLevelString[idx];
}