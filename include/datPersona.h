#ifndef DATPERSONA_H
#define DATPERSONA_H

#include "Utils.h"

#define PERSONA_FLAG_VALID      (1 << 0) // not sure of this name
#define PERSONA_FLAG_HEART_ITEM (1 << 2)

#define PERSONA_MAX_SKILLS 8

typedef enum
{
    SKILL_SLASH_ATTACK,
    SKILL_AGI,
    SKILL_AGILAO,
    SKILL_AGIDYNE,
    SKILL_MARAGI,
    SKILL_MARAGION,
    SKILL_MARAGIDYNE,
    SKILL_MARALAGIDYNE,
    SKILL_008,
    SKILL_RAGNAROK,
    SKILL_GARU,
    SKILL_GARULA,
    SKILL_GARUDYNE,
    SKILL_MAGARU,
    SKILL_MAGARULA,
    SKILL_MAGARUDYNE,
    SKILL_010,
    SKILL_011,
    SKILL_PANTA_RHEI,
    SKILL_BUFU,
    SKILL_BUFULA,
    SKILL_BUFUDYNE,
    SKILL_MABUFU,
    SKILL_MABUFULA,
    SKILL_MABUFUDYNE,
    SKILL_019,
    SKILL_01A,
    SKILL_NIFLHEIM,
    SKILL_ZIO,
    SKILL_ZIONGA,
    SKILL_ZIODYNE,
    SKILL_MAZIO,
    SKILL_MAZIONGA,
    SKILL_MAZIODYNE,
    SKILL_022,
    SKILL_023,
    SKILL_THUNDER_REIGN,
    SKILL_REGENERATE1 = 547,
    SKILL_REGENERATE2,
    SKILL_REGENERATE3,
    SKILL_INVIGORATE1,
    SKILL_INVIGORATE2,
    SKILL_INVIGORATE3,
    SKILL_SPRINGOFLIFE1 = 607,
    SKILL_SPRINGOFLIFE2,
} Skills;

typedef enum
{
    PERSONA_STAT_STRENGTH,
    PERSONA_STAT_MAGIC,
    PERSONA_STAT_ENDURANCE,
    PERSONA_STAT_AGILITY,
    PERSONA_STAT_LUCK,
    PERSONA_STAT_MAX
} PersonaStats;

// 52 bytes
typedef struct DatPersonaWork
{
    u16 flags;
    u16 id;
    u8 level;
    u32 nextExp;                       // For characters other than HERO, their exp is linked to their persona
    u16 skills[PERSONA_MAX_SKILLS];    // See enum 'Skills'
    u8 naturalStats[PERSONA_STAT_MAX]; // stats gained naturally. See enum PersonaStats
    u8 bonusStats[PERSONA_STAT_MAX];   // stats gained through incense cards. See enum PersonaStats
    u8 stats3[PERSONA_STAT_MAX];       // ??
} DatPersonaWork;

u8 datPersonaGetLevel(DatPersonaWork* persona);
u8 datPersonaGetLevelByPcId(u16 pcId);
u32 datPersonaGetNextExp(DatPersonaWork* persona);
u16* datPersonaGetSkills(DatPersonaWork* persona);
u16* datPersonaGetSkillsByPcId(u16 pcId);
u16 datPersonaGetTotalStat(DatPersonaWork* persona, u16 statId);
u8 datPersonaGetNaturalStat(DatPersonaWork* persona, u16 statId);
u8 datPersonaGetBonusStat(DatPersonaWork* persona, u16 statId);
void datPersonaSetBonusStatByPcId(u16 pcId, u16 statId, u8 amount);
void datPersonaAddToBonusStatByPcId(u16 pcId, u16 statId, s8 amount);
u8 datPersonaGetStat3(DatPersonaWork* persona, u16 statId);
u16 datPersonaAddToNaturalStat(DatPersonaWork* persona, u16 statId, s8 amount);
u16 datPersonaAddToNaturalStatHeroPersona(u16 heroPersonaIdx, u16 statId, s8 amount);

DatPersonaWork* datPersonaGetByPcId(u16 pcId);
u8 datPersonaHeroPersonaValid(u16 heroPersonaIdx);
DatPersonaWork* datPersonaGetHeroPersona(u16 heroPersonaIdx);
void datPersonaClearHeroPersonas();

void datPersonaAddExp(DatPersonaWork* persona, u32 exp);
void datPersonaMoveValidSkillsOnTop(DatPersonaWork* persona);
u8 datPersonaSetSkill(DatPersonaWork* persona, u16 skillId);
u8 datPersonaResetSkill(DatPersonaWork* persona, u16 skillId);
s32 datPersonaFindSkillIdx(DatPersonaWork* persona, u16 skillId);
u32 datPersonaCountValidSkills(DatPersonaWork* persona);

#endif