#ifndef H_SND_H
#define H_SND_H

#include "Utils.h"

#define HSND_BGM_PLAYING     1
#define HSND_BGM_NOT_PLAYING 0

typedef enum
{
    HSND_BGM_TARTARUS_THEBEL = 1,            // 01.ADX (1st block, also used for Monad)
    HSND_BGM_MASS_DESTRUCTION,               // 26.ADX (Id in the code is 2 but ADX id = 26)
    HSND_BGM_SHADOW = 19,                    // 19.ADX
    HSND_BGM_DEEP_BREATH,                    // 20.ADX
    HSND_BGM_BASEMENT,                       // 21.ADX
    HSND_BGM_DEEP_MENTALITY,                 // 22.ADX
    HSND_BGM_DEEP_BREATH_2,                  // 23.ADX (unused)
    HSND_BGM_DEEP_BREATH_3,                  // 24.ADX (unused)
    HSND_BGM_MOON_REACHING_OUT_STARS,        // 25.ADX
    HSND_BGM_MASTER_OF_SHADOW = 27,          // 27.ADX
    HSND_BGM_UNAVOIDABLE_BATTLE,             // 28.ADX (strega battle ost)
    HSND_BGM_BURN_MY_DREAD_LAST,             // 29.ADX
    HSND_BGM_BATTLE_HYMN_OF_SOUL,            // 30.ADX (nyx battle)
    HSND_BGM_MASTER_OF_TARTARUS,             // 31.ADX (tartarus bosses)
    HSND_BGM_KYOTO,                          // 32.ADX
    HSND_BGM_TROUBLED = 35,                  // 35.ADX
    HSND_BGM_ESCAPED_THE_DARKNESS,           // 36.ADX
    HSND_BGM_LIVING_WITH_DETERMINATION,      // 37.ADX
    HSND_BGM_JOY_1,                          // 38.ADX
    HSND_BGM_FEARFUL_EXPERIENCE,             // 39.ADX
    HSND_BGM_CALAMITY,                       // 40.ADX
    HSND_BGM_JOY_2 = 43,                     // 43.ADX
    HSND_BGM_MYSTERIOUS_FEELING,             // 44.ADX
    HSND_BGM_CRISIS,                         // 45.ADX
    HSND_BGM_PATH_IS_OPEN,                   // 46.ADX (social link level 10)
    HSND_BGM_WANT_TO_BE_CLOSE = 50,          // 50.ADX
    HSND_BGM_CHANGING_SEASONS,               // 51.ADX
    HSND_BGM_MEMORIES_OF_SCHOOL_1,           // 52.ADX (school during january)
    HSND_BGM_IWATODAI_DORM,                  // 53.ADX
    HSND_BGM_ARIA_OF_THE_SOUL,               // 54.ADX
    HSND_BGM_TANAKA_AMAZING_COMM,            // 55.ADX
    HSND_BGM_PAULOWNIA_MALL,                 // 56.ADX
    HSND_BGM_AFTER_BATTLE = 60,              // 60.ADX
    HSND_BGM_UNK_34,                         // 61.ADX (unused)
    HSND_BGM_PATH_WAS_CLOSED,                // 62.ADX (game over)
    HSND_BGM_TARTARUS_ARQA = 70,             // 70.ADX (tartarus 2nd block)
    HSND_BGM_VOICE_SOMEONE_CALLS,            // 71.ADX (tartarus 1st floor)
    HSND_BGM_TARTARUS_TZIAH,                 // 72.ADX (tartarus 4th block)
    HSND_BGM_TARTARUS_HARABAH,               // 73.ADX (tartarus 5th block)
    HSND_BGM_TARTARUS_ADAMAH_1,              // 74.ADX (tartarus 6rd block)
    HSND_BGM_TARTARUS_ADAMAH_2,              // 75.ADX (tartarus 6th block again)
    HSND_BGM_DEEP_MENTALITY_2,               // 76.ADX (unused)
    HSND_BGM_LIVING_WITH_DETERMINATION_DORM, // 77.ADX (dorm during january)
    HSND_BGM_AFTER_BATTLE_2,                 // 78.ADX
    HSND_BGM_MISTIC,                         // 79.ADX
    HSND_BGM_MEMORIES_OF_CITY,               // 80.ADX (city during january)
    HSND_BGM_TARTARUS_YABBASHAH,             // 81.ADX (tartarus 3rd block)
    HSND_BGM_UNK_48,                         // 82.ADX
    HSND_BGM_UNK_49,                         // 83.ADX
    HSND_BGM_UNK_50,                         // 84.ADX
    HSND_BGM_TRANQUILITY,                    // 85.ADX
    HSND_BGM_SOCIAL_LINK_UP,                 // 86.ADX
    HSND_BGM_ADVENTURED_ACT,                 // 87.ADX
    HSND_BGM_MEMORIES_OF_SCHOOL_2,           // 88.ADX (march 5th)
    HSND_BGM_DURING_THE_TEST,                // 89.ADX (exam)
    HSND_BGM_UNK_56,                         // 90.ADX
    HSND_BGM_AFTERNOON_BREAK,                // 91.ADX
    HSND_BGM_UNK_58,                         // 92.ADX
    HSND_BGM_VELVET_ROOM_FINAL,              // 93.ADX
    HSND_BGM_MASS_DESTRUCTION_FES = 106,     // 106.ADX
    HSND_BGM_HEARTFUL_CRY = 113,             // 113.ADX
    HSND_BGM_DARKNESS,                       // 114.ADX (the answer final boss)
    HSND_BGM_MAIN_MENU,                      // 115.ADX
    HSND_BGM_NONE = -1,
} BgmId;

// ?? bytes
typedef struct BgmWork
{
    u32 isBgmPlaying;     // See 'HSND_BGM_*'
    u32 unk2;
    s16 id;               // See 'BgmId' enum
    u16 unk3;
    u16 unk4;
    u32 unk5;
    u16 unk6;
    char* currAdxString;
} BgmWork;

s16 H_Snd_GetCurrentBgmId();
void H_Snd_StopBgm();
void H_Snd_StopBgmFade(s16 fadeDuration);
u8 H_Snd_PlayBgm(s16 id, s32 unused);
u8 H_Snd_FUN_00109ca0(s16 param_1, s16 param_2);

#endif