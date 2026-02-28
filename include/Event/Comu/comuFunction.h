#ifndef COMUFUNCTION_H
#define COMUFUNCTION_H

#include "Utils.h"

// 24 bytes
typedef struct SiteibiEvent
{
    u8 startMonth;       // 0x00
    u8 startDay;         // 0x01
    u8 startTime;        // 0x02
    u16 scrPrcdIdx;      // 0x04. Procedure index of the event in 'SiteibiEvent.BF' file
    u8 unk_06;           // 0x06
    u8 unk_07;           // 0x07
    u8 endMonth;         // 0x08
    u8 endDay;           // 0x09
    u8 endTime;          // 0x0a
    u8 slID;             // 0x0b. Social link ID. Is equal to 'SOCIAL_LINK_NONE' if event is unrelated to social links
    u16 slLvlReq;        // 0x0c. Social link level requirement
    u16 gflagReqOn1;     // 0x0e. first 'G_FLAG_*' that needs to be true
    u16 gflagReqOn2;     // 0x10. second 'G_FLAG_*' that needs to be true
    u16 gflagReqOff1;    // 0x12. first 'G_FLAG_*' that needs to be false
    u16 gflagReqOff2;    // 0x14. second 'G_FLAG_*' that needs to be false
    u16 gflagToActivate; // 0x16. 'G_FLAG_*' that the event needs to activate
} SiteibiEvent;

#endif