/*This file is horrible*/

#ifndef G_DATA_H
#define G_DATA_H

#include "datUnit.h"
#include "datPersona.h"
#include "datCalendar.h"

#define MAX_CHARACTER_LEVEL 99

#define IS_HERO(characterId) ((characterId) == CHARACTER_HERO)

#define SOCIAL_STAT_MIN_POINT 0
#define SOCIAL_STAT_MAX_POINT 999

typedef enum
{
    SCENARIO_MODE_JOURNEY,
    SCENARIO_MODE_ANSWER
} ScenarioMode; 

typedef enum
{
    CHARACTER_NONE,
    CHARACTER_HERO,
    CHARACTER_YUKARI,
    CHARACTER_AIGIS,
    CHARACTER_MITSURU,
    CHARACTER_JUNPEI,
    CHARACTER_FUUKA,
    CHARACTER_AKIHIKO,
    CHARACTER_KEN,
    CHARACTER_SHINJIRO_OR_METIS, // Shinjiro if playing The Journey, Metis if The Answer
    CHARACTER_KOROMARU,
    CHARACTER_MAX
} CharactersEnum;

typedef enum
{
    ARCANA_00,
    ARCANA_FOOL,
    ARCANA_MAGICIAN,
    ARCANA_PRIESTESS,
    ARCANA_EMPRESS,
    ARCANA_EMPEROR,
    ARCANA_HIERORPHTANT,
    ARCANA_LOVERS,
    ARCANA_CHARIOT,
    ARCANA_JUSTICE,
    ARCANA_HERMIT,
    ARCANA_FORTUNE,
    ARCANA_STRENGTH,
    ARCANA_HANGED_MAN,
    ARCANA_DEATH,
    ARCANA_TOWER,
    ARCANA_STAR,
    ARCANA_MOON,
    ARCANA_SUN,
    ARCANA_JUDGMENT,
    ARCANA_AEON,
    ARCANA_17,
    ARCANA_18,
    ARCANA_19,
    ARCANA_1A,
    ARCANA_1B,
    ARCANA_1C,
    ARCANA_1D,
    ARCANA_1E,
    ARCANA_1F,
} Arcanas;

typedef enum
{
    SOCIAL_LINK_NONE = -1,
    SOCIAL_LINK_SEES,
    SOCIAL_LINK_KENJI,
    SOCIAL_LINK_HIDETOSHI = 4,
    SOCIAL_LINK_OLD_COUPLE,
    SOCIAL_LINK_YUKARI,
    SOCIAL_LINK_FUUKA,
    SOCIAL_LINK_MITSURU,
    SOCIAL_LINK_AIGIS,
    SOCIAL_LINK_YUKO,
    SOCIAL_LINK_CHIHIRO,
    SOCIAL_LINK_KAZUSHI_TRACK,
    SOCIAL_LINK_KAZUSHI_KENDO,
    SOCIAL_LINK_KAZUSHI_SWIM,
    SOCIAL_LINK_MAYA = 16,
    SOCIAL_LINK_KEISUKE_PHOTO,
    SOCIAL_LINK_KEISUKE_ART,
    SOCIAL_LINK_KEISUKE_MUSIC,
    SOCIAL_LINK_MAIKO = 21,
    SOCIAL_LINK_PHAROS,
    SOCIAL_LINK_BEBE,
    SOCIAL_LINK_TANAKA,
    SOCIAL_LINK_MUTATSU,
    SOCIAL_LINK_MAMORU,
    SOCIAL_LINK_NOZOMI,
    SOCIAL_LINK_AKINARI,
    SOCIAL_LINK_NYX_TEAM,
} PlayerSocialLink;

typedef enum
{
    PHYSICAL_CONDITION_GOOD,
    PHYSICAL_CONDITION_UNK1, // not in final game 
    PHYSICAL_CONDITION_GREAT,
    PHYSICAL_CONDITION_TIRED,
    PHYSICAL_CONDITION_UNK2, // not in final game 
    PHYSICAL_CONDITION_SICK
} CharacterPhysicalCondition;

typedef enum
{
    AI_TACTIC_ACT_FREELY = 1,
    AI_TACTIC_KNOCK_DOWN,
    AI_TACTIC_ATTACK_FALLEN,
    AI_TACTIC_FULL_ASSAULT,
    AI_TACTIC_HEAL_SUPPORT,
    AI_TACTIC_CONSERVE_SP,
    AI_TACTIC_ASSIGN_TARGET,
    AI_TACTIC_SAME_TARGET,
    AI_TACTIC_STAND_BY,
    AI_TACTIC_ORGIA_MODE,
    AI_TACTIC_MAX
} AiTactic;

typedef enum
{
    EQUIPMENT_TYPE_WEAPON,
    EQUIPMENT_TYPE_ARMOR,
    EQUIPMENT_TYPE_BOOTS,
    EQUIPMENT_TYPE_ACCESSORY
} EquimentTypes;

typedef enum
{
    WEAPON_TYPE_1H_SWORD,
    WEAPON_TYPE_2H_SWORD,
    WEAPON_TYPE_AXE,
    WEAPON_TYPE_FIST,
    WEAPON_TYPE_SPEAR,
    WEAPON_TYPE_KNIFE,
    WEAPON_TYPE_BOW,
    WEAPON_TYPE_GUN
} WeaponTypes;

// 6 bytes
typedef struct
{
    u16 academicPoint;
    u16 charmPoint;
    u16 couragePoint;
} SocialStats;

// 6 bytes
typedef struct 
{
    u16 physicalCondition; // See enum CharacterPhysicalCondition
    u16 fatigueCounter;    // if 0, character will become tired
    u16 oldFatigueCounter; // value before entering tartarus
} PhysicalState;

// 20 bytes
typedef struct 
{
    u16 id;
    u32 type;
    u8 cUnk1;
    u8 effect;
    u16 firstStat;
    u16 secondStat;
    u16 sUnk2;
    u8 unkData[0x04];
} EquipmentData;

// 16 bytes
typedef struct
{
    u16 equipmentsIdx[4];      // See enum EquipmentTypes to access each idx
    EquipmentData* equipments; // 00836794 -> 010c15f0
    void* unkPtr;              // 00836798 -> 010c2d90
} PlayerEquipmentData;

typedef struct
{
    u16 equippedPersona;      // 0 to 11
    PersonaData personas[12];
} PlayerPersonaData;

typedef struct
{
    SocialStats socialStats;
    u32 nextExp;
    PhysicalState physicalState;
    u16 activeSocialLink;
    u8 socialLinkStat[29];
} PlayerStatusData;

// 868 bytes
typedef struct
{
    UnitData unit;
    SocialStats socialStats;
    u8 unkData1[0x06];
    PhysicalState physicalState;
    u16 equipmentsIdx[4];         // always 0, 1, 2, 3
    EquipmentData equipments[4];
    u8 unkData2[0x4C];
    PersonaData persona;
    u8 unkData3[0x297]; // TODO
} CharacterData;

extern CharacterData gCharacters[CHARACTER_MAX - 1];

extern PlayerPersonaData gPlayerPersonaData;

void Global_SetScenarioMode(u32 scenario);
u32 Global_GetScenarioMode();

void FUN_0016f3e0(u32 idx, u32 value);

UnitData* Character_GetUnit(u16 characterId);
void Character_InitUnitData(u16 characterId);
u8 Character_GetLevel(u16 characterId);
u16 Persona_GetPersonaId(u16 characterId);
u32 Character_GetBattleFlagsNoDown(u16 characterId);
void Character_AddBattleFlags(u16 characterId, u32 flags);
void Character_SetOldFatigueCounter(u16 characterId, u16 oldFatigueCounter);
void Character_RemoveBattleFlags(u16 characterId, u32 flags);
u32 Character_GetExpUntilNextLevel(u16 characterId);
u8 Character_DidCharacterLevelUp(u16 characterId, u32 expGain);
void Character_SetAiTactic(u16 characterId, u8 aiTacticId);
u8 Character_GetAiTactic(u16 characterId);
void Character_SetPhysicalCondition(u16 characterId, u16 physicalCondition);
void Character_SetFatigueCounter(u16 characterId, u16 fatigueCounter);
void Character_SetHealth(u16 characterId, u16 health);
void Character_SetActiveSocialLink(u16 activeSocialLink);
u16 CalendarData_GetDaysSinceApr5();
u8 CalendarData_GetTime();
u16 CalendarData_GetDaysSkipTarget();
u8 CalendarData_GetTimeSkipTarget();
u32 CalendarData_GetSkipToTarget();
void Character_SetAcademicPoint(u16 characterId, u16 academicPoint);
void Character_SetCharmPoint(u16 characterId, u16 charmPoint);
void Character_SetCouragePoint(u16 characterId, u16 couragePoint);
u16 Character_GetAcademicPoint(u16 characterId);
u16 Character_GetCharmPoint(u16 characterId);
u16 Character_GetCouragePoint(u16 characterId);
u16 Character_GetAcademicLevel(u16 academicPoint);
u16 Character_GetCharmLevel(u16 charmPoint);
u16 Character_GetCourageLevel(u16 couragePoint);
u32 Character_GetNextExp(u16 characterId);
u16 Character_GetPhysicalCondition(u16 characterId);
u16 Character_GetEquipmentIdx(u16 characterId, u16 equipmentType);
void CalendarData_SetDaysSinceApr5(u16 daysSinceApr5);
void CalendarData_SetTime(u8 time);
void CalendarData_SetDaysSkipTarget(u16 days);
void CalendarData_SetTimeSkipTarget(u8 time);
void CalendarData_SetSkipToTarget(u32 val);
void Global_SetGlobalFlag(u32 bit, u8 enabled);
void Global_ResetGlobalFlags();
u16 Character_GetEquipmentId(u16 characterId, u16 equipmentIdx);
u8 Character_GetEquipmentEffect(u16 characterId, u16 equipmentIdx);
void Compendium_Init();
u16 Player_GetActiveSocialLink();
u8 Player_GetSocialLinkLevel(u16 socialLink);
PersonaData* Compendium_GetPersonaByIdx(s32 idx);

void P3FES_ASSERT(const char* file, const u32 line);
void FUN_001052b0(const char* fmt, ...);
void FUN_005225a8(const char* fmt, ...);

#endif // G_DATA_H