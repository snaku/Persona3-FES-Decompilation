#include "Battle/btlSound.h"
#include "Battle/battle.h"
#include "g_data.h"
#include "h_snd.h"

// FUN_002dcd30
void btlSoundPlayBgm()
{
    BtlEncountTable* encount;

    if (gBtl->flags & BTL_FLAG_UNK40)
    {
        encount = &gEncountTbl[gBtl->startInfo.enmUnits->encountId];

        switch (encount->bgm)
        {
            case BTLENCOUNT_BGM_FULLMOON:     H_Snd_PlayBgm(BGM_ID_MASTER_OF_SHADOW, 1);    break;
            case BTLENCOUNT_BGM_STREGA:       H_Snd_PlayBgm(BGM_ID_UNAVOIDABLE_BATTLE, 1);  break;
            case BTLENCOUNT_BGM_TARTARUSBOSS: H_Snd_PlayBgm(BGM_ID_MASTER_OF_TARTARUS, 1);  break;
            case BTLENCOUNT_BGM_NYX:          H_Snd_PlayBgm(BGM_ID_BURN_MY_DREAD_LAST, 1);  break;
            case BTLENCOUNT_BGM_NYXAVATAR:    H_Snd_PlayBgm(BGM_ID_BATTLE_HYMN_OF_SOUL, 1); break;
            case BTLENCOUNT_BGM_SEES:         H_Snd_PlayBgm(BGM_ID_HEARTFUL_CRY, 1);        break;
            case BTLENCOUNT_BGM_EREBUS:       H_Snd_PlayBgm(BGM_ID_DARKNESS, 1);            break;

            default:
                if (datGetScenarioMode() == SCENARIO_MODE_JOURNEY)
                {
                    H_Snd_PlayBgm(BGM_ID_MASS_DESTRUCTION, 1);
                }
                else
                {
                    H_Snd_PlayBgm(BGM_ID_MASS_DESTRUCTION_FES, 1);
                }
        }
    }
}