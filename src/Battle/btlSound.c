#include "Battle/btlSound.h"
#include "Battle/battle.h"
#include "Battle/btlPacket.h"
#include "g_data.h"
#include "h_snd.h"
#include "h_cdvd.h"
#include "temporary.h"

// FUN_002dcd30
void btlSoundPlayBgm()
{
    BtlEncountTable* encount;

    if (gBtl->flags & BTL_FLAG_UNK40)
    {
        encount = &gEncountTbl[gBtl->startInfo.enmUnits->encountId];

        switch (encount->bgm)
        {
            case BTLENCOUNT_BGM_FULLMOON:     H_Snd_PlayBgm(HSND_BGM_MASTER_OF_SHADOW, 1);    break;
            case BTLENCOUNT_BGM_STREGA:       H_Snd_PlayBgm(HSND_BGM_UNAVOIDABLE_BATTLE, 1);  break;
            case BTLENCOUNT_BGM_TARTARUSBOSS: H_Snd_PlayBgm(HSND_BGM_MASTER_OF_TARTARUS, 1);  break;
            case BTLENCOUNT_BGM_NYX:          H_Snd_PlayBgm(HSND_BGM_BURN_MY_DREAD_LAST, 1);  break;
            case BTLENCOUNT_BGM_NYXAVATAR:    H_Snd_PlayBgm(HSND_BGM_BATTLE_HYMN_OF_SOUL, 1); break;
            case BTLENCOUNT_BGM_SEES:         H_Snd_PlayBgm(HSND_BGM_HEARTFUL_CRY, 1);        break;
            case BTLENCOUNT_BGM_EREBUS:       H_Snd_PlayBgm(HSND_BGM_DARKNESS, 1);            break;

            default:
                if (datGetScenarioMode() == SCENARIO_MODE_JOURNEY)
                {
                    H_Snd_PlayBgm(HSND_BGM_MASS_DESTRUCTION, 1);
                }
                else
                {
                    H_Snd_PlayBgm(HSND_BGM_MASS_DESTRUCTION_FES, 1);
                }
        }
    }
}

// FUN_002dd270
void btlSoundInitSkillSEPacket(void* work)
{
    BtlSoundPacketSkillSE* packet;
    char buffer[128];

    packet = (BtlSoundPacketSkillSE*)work;

    if (!(packet->flags & BTLSOUND_SKILLSE_FLAG_UNK01))
    {
        sprintf(buffer, "%s%03X.se", "skill/", packet->skillId);
        packet->cdvd = H_Cdvd_Request(buffer, HCDVD_FILENORMAL);
    }
    else
    {
        packet->cdvd = NULL;
    }

    packet->state = 1;
    packet->timer = 0;
}

// FUN_002dd2f0
u32 btlSoundUpdateSkillSEPacket(void* work)
{
    // TODO

    return false;
}

// FUN_002dd4a0
BtlPacket* btlSoundCreateSkillSEPacket(u16 skillId, u16 flags)
{
    BtlPacket* packet;
    BtlSoundPacketSkillSE* work;

    packet = btlPacketCreate(BTLSOUND_PACKET_SKILLSE, sizeof(BtlSoundPacketSkillSE));

    packet->unk_47 &= ~(1 << 0);
    packet->initFunc = btlSoundInitSkillSEPacket;
    packet->updateFunc = btlSoundUpdateSkillSEPacket;

    work = (BtlSoundPacketSkillSE*)packet->workData;

    work->skillId = skillId;
    work->flags = flags;

    return packet;
}