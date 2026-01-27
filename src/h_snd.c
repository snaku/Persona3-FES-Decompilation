#include "h_snd.h"

// 007cb2a8. See enum BgmId
static const char* bgmStrings[82] = 
{
    "01.ADX", "26.ADX", "19.ADX", "20.ADX", "21.ADX",
    "22.ADX", "23.ADX", "24.ADX", "25.ADX", "27.ADX",
    "28.ADX", "29.ADX", "30.ADX", "31.ADX", "32.ADX",
    "35.ADX", "36.ADX", "37.ADX", "38.ADX", "39.ADX",
    "40.ADX", "43.ADX", "44.ADX", "45.ADX", "46.ADX",
    "50.ADX", "51.ADX", "52.ADX", "53.ADX", "54.ADX",
    "55.ADX", "56.ADX", "60.ADX", "61.ADX", "62.ADX",
    "63.ADX", "70.ADX", "71.ADX", "72.ADX", "73.ADX",
    "74.ADX", "75.ADX", "76.ADX", "77.ADX", "78.ADX",
    "79.ADX", "80.ADX", "81.ADX", "82.ADX","83.ADX",
    "84.ADX", "85.ADX", "86.ADX", "87.ADX", "88.ADX",
    "89.ADX", "90.ADX", "91.ADX", "92.ADX", "93.ADX",
    "94.ADX", "95.ADX", "96.ADX", "97.ADX", "98.ADX",
    "99.ADX", "100.ADX", "101.ADX", "102.ADX", "103.ADX",
    "104.ADX", "105.ADX", "106.ADX", "107.ADX", "108.ADX",
    "109.ADX", "110.ADX", "111.ADX", "112.ADX", "113.ADX",
    "114.ADX", "115.ADX"
};

static BgmData bgm;

// FUN_00108e50
u16 H_Snd_GetCurrentBgmId()
{
    if (bgm.isBgmPlaying == H_SND_BGM_NOT_PLAYING)
    {
        return BGM_ID_NONE;
    }

    return bgm.currBgmId;
}

// FUN_00108e50
void H_Snd_StopPlayingBgm()
{
    if (bgm.isBgmPlaying != H_SND_BGM_NOT_PLAYING)
    {
        // FUN_0054d100(bgm.unk5);
        bgm.isBgmPlaying = H_SND_BGM_NOT_PLAYING;
        bgm.unk4 = 0;
        bgm.currBgmId = BGM_ID_NONE;
    }
}

// FUN_001099d0
u32 H_Snd_PlayBgm(u16 bgmId, u8 param_2)
{
    // TODO
    u16 currBgmId = bgm.currBgmId;

    if (bgm.isBgmPlaying == H_SND_BGM_NOT_PLAYING)
    {
        currBgmId = BGM_ID_NONE;
    }

    if (bgmId != currBgmId)
    {
        bgm.unk2 = 0;
        bgm.isBgmPlaying = H_SND_BGM_PLAYING;
        bgm.unk3 = 1;
        // DAT_007e4560 = bgm.currBgmId;
        bgm.unk5 = 0;
        bgm.currBgmId = bgmId;
        P3FES_LOG2("", bgm.currBgmAdxString, bgmStrings[bgmId]);
    }

    return H_SND_BGM_PLAYING;
}

// FUN_00109ca0
u8 H_Snd_FUN_00109ca0(s16 param_1, s16 param_2)
{
    // TODO

    return true;
}

// FUN_00523ac8. TEMPORARY IN THIS FILE !
void P3FES_LOG2(const char* fmt, ...)
{
    // TODO
}