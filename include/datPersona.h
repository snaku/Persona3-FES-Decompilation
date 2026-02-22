#ifndef DATPERSONA_H
#define DATPERSONA_H

#include "Utils.h"

#define PERSONA_FLAG_VALID      (1 << 0) // not sure of this name
#define PERSONA_FLAG_HEART_ITEM (1 << 2)

#define PERSONA_MAX_SKILLS 8

// Found in BATTLE/MSG.TBL
typedef enum
{
    PERSONA_SKILL_SLASH_ATTACK,
    PERSONA_SKILL_AGI,
    PERSONA_SKILL_AGILAO,
    PERSONA_SKILL_AGIDYNE,
    PERSONA_SKILL_MARAGI,
    PERSONA_SKILL_MARAGION,
    PERSONA_SKILL_MARAGIDYNE,
    PERSONA_SKILL_MARALAGIDYNE,
    PERSONA_SKILL_008,
    PERSONA_SKILL_RAGNAROK,
    PERSONA_SKILL_GARU,
    PERSONA_SKILL_GARULA,
    PERSONA_SKILL_GARUDYNE,
    PERSONA_SKILL_MAGARU,
    PERSONA_SKILL_MAGARULA,
    PERSONA_SKILL_MAGARUDYNE,
    PERSONA_SKILL_010,
    PERSONA_SKILL_011,
    PERSONA_SKILL_PANTA_RHEI,
    PERSONA_SKILL_BUFU,
    PERSONA_SKILL_BUFULA,
    PERSONA_SKILL_BUFUDYNE,
    PERSONA_SKILL_MABUFU,
    PERSONA_SKILL_MABUFULA,
    PERSONA_SKILL_MABUFUDYNE,
    PERSONA_SKILL_019,
    PERSONA_SKILL_01A,
    PERSONA_SKILL_NIFLHEIM,
    PERSONA_SKILL_ZIO,
    PERSONA_SKILL_ZIONGA,
    PERSONA_SKILL_ZIODYNE,
    PERSONA_SKILL_MAZIO,
    PERSONA_SKILL_MAZIONGA,
    PERSONA_SKILL_MAZIODYNE,
    PERSONA_SKILL_022,
    PERSONA_SKILL_023,
    PERSONA_SKILL_THUNDER_REIGN,
} PersonaSkills;

typedef enum
{
    PERSONA_STAT_STRENGTH,
    PERSONA_STAT_MAGIC,
    PERSONA_STAT_ENDURANCE,
    PERSONA_STAT_AGILITY,
    PERSONA_STAT_LUCK,
    PERSONA_STAT_MAX
} PersonaStats;

// 52 bytes, not sure of the real size
typedef struct
{
    u16 flags;
    u16 id;
    u8 level;
    u32 nextExp;                       // For characters other than HERO, their exp is linked to their persona
    u16 skills[PERSONA_MAX_SKILLS];    // See enum PersonaSkills
    u8 naturalStats[PERSONA_STAT_MAX]; // stats gained naturally. See enum PersonaStats
    u8 bonusStats[PERSONA_STAT_MAX];   // stats gained through incense cards. See enum PersonaStats
    u8 stats3[PERSONA_STAT_MAX];       // ??
    // other data ?
} PersonaData; // For reference: Yukari = 008340ec

u8 Persona_GetPersonaLevel(PersonaData* persona);
u8 Persona_GetPersonaLevelCharacterId(u16 characterId);
u32 Persona_GetPersonaNextExp(PersonaData* persona);
u16* Persona_GetSkills(PersonaData* persona);
u16* Persona_GetSkillsByCharacterId(u16 characterId);
u16 Persona_GetTotalStat(PersonaData* persona, u16 statId);
u8 Persona_GetNaturalStat(PersonaData* persona, u16 statId);
u8 Persona_GetBonusStat(PersonaData* persona, u16 statId);
void Persona_SetBonusStatByCharacterId(u16 characterId, u16 statId, u8 amount);
void Persona_AddToBonusStatByCharacterId(u16 characterId, u16 statId, s8 amount);
u8 Persona_GetStat3(PersonaData* persona, u16 statId);
u16 Persona_AddToNaturalStat(PersonaData* persona, u16 statId, s8 amount);
u16 Persona_AddToNaturalStatHeroPersonaIdx(u16 heroPersonaIdx, u16 statId, s8 amount);

PersonaData* Persona_GetPersonaByCharacterId(u16 characterId);
u8 Persona_IsHeroPersonaValid(u16 heroPersonaIdx);
PersonaData* Persona_GetHeroPersona(u16 heroPersonaIdx);

void Persona_AddExp(PersonaData* persona, u32 exp);

void Persona_MoveValidSkillsOnTop(PersonaData* persona);
u8 Persona_SetSkill(PersonaData* persona, u16 skillId);
u8 Persona_ResetSkill(PersonaData* persona, u16 skillId);
s32 Persona_FindPersonaSkillIdx(PersonaData* persona, u16 skillId);
u32 Persona_CountValidSkills(PersonaData* persona);

#endif