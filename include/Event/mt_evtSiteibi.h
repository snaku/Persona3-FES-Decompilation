#ifndef MT_EVTSITEIBIIDX_H
#define MT_EVTSITEIBIIDX_H

#include "Utils.h"

// 'Siteibi' is maybe a typo.
// It should be 'Shiteibi' which means 'fixed date' in japanese 
// so SiteibiEvent = FixedDateEvent

// To use for a 'SiteibiEvent' array
typedef enum
{
    EVENT_SITEIBI_GAME_MODE,
    EVENT_SITEIBI_INTRO_ANIME_CS, 
    // TODO
} EventSiteibiIdx;

// 24 bytes
typedef struct SiteibiEvent
{
    u8 month;            // 0x00
    u8 day;              // 0x01
    u8 time;             // 0x02
    u16 scrPrcdIdx;      // 0x04. Procedure index of the event in 'SiteibiEvent.BF' file
    u8 unkData2[0x10];
    u16 gflagToActivate; // 0x16. 'G_FLAG_*' that the event needs to activate
} SiteibiEvent;

#endif