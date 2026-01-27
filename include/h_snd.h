#ifndef H_SND_H
#define H_SND_H

#include "Utils.h"

#define H_SND_BGM_PLAYING     1
#define H_SND_BGM_NOT_PLAYING 0

typedef enum
{
    BGM_ID_TARTARUS_THEBEL = 1,            // 01.ADX (1st block, also used for Monad)
    BGM_ID_MASS_DESTRUCTION,               // 26.ADX (Id in the code is 2 but ADX id = 26)
    BGM_ID_SHADOW = 19,                    // 19.ADX
    BGM_ID_DEEP_BREATH,                    // 20.ADX
    BGM_ID_BASEMENT,                       // 21.ADX
    BGM_ID_DEEP_MENTALITY,                 // 22.ADX
    BGM_ID_DEEP_BREATH_2,                  // 23.ADX (unused)
    BGM_ID_DEEP_BREATH_3,                  // 24.ADX (unused)
    BGM_ID_MOON_REACHING_OUT_STARS,        // 25.ADX
    BGM_ID_MASTER_OF_SHADOW = 27,          // 27.ADX
    BGM_ID_UNAVOIDABLE_BATTLE,             // 28.ADX (strega battle ost)
    BGM_ID_BURN_MY_DREAD_LAST,             // 29.ADX
    BGM_ID_BATTLE_HYMN_OF_SOUL,            // 30.ADX (nyx battle)
    BGM_ID_MASTER_OF_TARTARUS,             // 31.ADX (tartarus bosses)
    BGM_ID_KYOTO,                          // 32.ADX
    BGM_ID_TROUBLED = 35,                  // 35.ADX
    BGM_ID_ESCAPED_THE_DARKNESS,           // 36.ADX
    BGM_ID_LIVING_WITH_DETERMINATION,      // 37.ADX
    BGM_ID_JOY_1,                          // 38.ADX
    BGM_ID_FEARFUL_EXPERIENCE,             // 39.ADX
    BGM_ID_CALAMITY,                       // 40.ADX
    BGM_ID_JOY_2 = 43,                     // 43.ADX
    BGM_ID_MYSTERIOUS_FEELING,             // 44.ADX
    BGM_ID_CRISIS,                         // 45.ADX
    BGM_ID_PATH_IS_OPEN,                   // 46.ADX (social link level 10)
    BGM_ID_WANT_TO_BE_CLOSE = 50,          // 50.ADX
    BGM_ID_CHANGING_SEASONS,               // 51.ADX
    BGM_ID_MEMORIES_OF_SCHOOL_1,           // 52.ADX (school during january)
    BGM_ID_IWATODAI_DORM,                  // 53.ADX
    BGM_ID_ARIA_OF_THE_SOUL,               // 54.ADX
    BGM_ID_TANAKA_AMAZING_COMM,            // 55.ADX
    BGM_ID_PAULOWNIA_MALL,                 // 56.ADX
    BGM_ID_AFTER_BATTLE = 60,              // 60.ADX
    BGM_ID_UNK_34,                         // 61.ADX (unused)
    BGM_ID_PATH_WAS_CLOSED,                // 62.ADX (game over)
    BGM_ID_TARTARUS_ARQA = 70,             // 70.ADX (tartarus 2nd block)
    BGM_ID_VOICE_SOMEONE_CALLS,            // 71.ADX (tartarus 1st floor)
    BGM_ID_TARTARUS_TZIAH,                 // 72.ADX (tartarus 4th block)
    BGM_ID_TARTARUS_HARABAH,               // 73.ADX (tartarus 5th block)
    BGM_ID_TARTARUS_ADAMAH_1,              // 74.ADX (tartarus 6rd block)
    BGM_ID_TARTARUS_ADAMAH_2,              // 75.ADX (tartarus 6th block again)
    BGM_ID_DEEP_MENTALITY_2,               // 76.ADX (unused)
    BGM_ID_LIVING_WITH_DETERMINATION_DORM, // 77.ADX (dorm during january)
    BGM_ID_AFTER_BATTLE_2,                 // 78.ADX
    BGM_ID_MISTIC,                         // 79.ADX
    BGM_ID_MEMORIES_OF_CITY,               // 80.ADX (city during january)
    BGM_ID_TARTARUS_YABBASHAH,             // 81.ADX (tartarus 3rd block)
    BGM_ID_UNK_48,                         // 82.ADX
    BGM_ID_UNK_49,                         // 83.ADX
    BGM_ID_UNK_50,                         // 84.ADX
    BGM_ID_TRANQUILITY,                    // 85.ADX
    BGM_ID_SOCIAL_LINK_UP,                 // 86.ADX
    BGM_ID_ADVENTURED_ACT,                 // 87.ADX
    BGM_ID_MEMORIES_OF_SCHOOL_2,           // 88.ADX (march 5th)
    BGM_ID_DURING_THE_TEST,                // 89.ADX (exam)
    BGM_ID_UNK_56,                         // 90.ADX
    BGM_ID_AFTERNOON_BREAK,                // 91.ADX
    BGM_ID_UNK_58,                         // 92.ADX
    BGM_ID_VELVET_ROOM_FINAL,              // 93.ADX
    BGM_ID_MAIN_MENU = 115,                // 115.ADX
    BGM_ID_NONE = 0xFFFF,
} BgmId;

// 007e4430
typedef struct 
{
    u32 isBgmPlaying;
    u32 unk2;
    u16 currBgmId;
    u16 unk3;
    u16 unk4;
    u32 unk5;
    u16 unk6;
    char* currBgmAdxString;
} BgmData;

u16 H_Snd_GetCurrentBgmId();
void H_Snd_StopPlayingBgm();
u32 H_Snd_PlayBgm(u16 bgmId, u8 param_2);
u8 H_Snd_FUN_00109ca0(s16 param_1, s16 param_2);

#endif