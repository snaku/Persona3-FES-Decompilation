#ifndef G_DATA_H
#define G_DATA_H

#include "Utils.h"

#define MAX_CHARACTERS CHARACTER_MAX - 1 // there's 10 characters in persona 3, but the player has its own struct
#define MAX_CHARACTER_LEVEL 99

#define MAX_AI_TACTIC_ID AI_TACTIC_MAX - 1

#define IS_HERO(characterId) ((characterId) == CHARACTER_HERO)

#define SOCIAL_STAT_MIN_POINT 0
#define SOCIAL_STAT_MAX_POINT 999

#define BATTLE_FLAG_CHARM    (1 << 0)  // 0x01
#define BATTLE_FLAG_DISTRESS (1 << 1)  // 0x02
#define BATTLE_FLAG_DIZZY    (1 << 2)  // 0x04
#define BATTLE_FLAG_FEAR     (1 << 3)  // 0x08
#define BATTLE_FLAG_RAGE     (1 << 4)  // 0x10
#define BATTLE_FLAG_FREEZE   (1 << 5)  // 0x20
#define BATTLE_FLAG_SHOCK    (1 << 6)  // 0x40
#define BATTLE_FLAG_POISON   (1 << 7)  // 0x80
#define BATTLE_FLAG_ORGIA    (1 << 8)  // 0x100
#define BATTLE_FLAG_OVERHEAT (1 << 9)  // 0x200
#define BATTLE_FLAG_DEAD     (1 << 19) // 0x80000
#define BATTLE_FLAG_DOWN     (1 << 20) // 0x100000

typedef enum
{
    GAME_SCENARIO_JOURNEY,
    GAME_SCENARIO_ANSWER
} GameScenario; 

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
    SOCIAL_LINK_NONE = 255 // value when player sleeps, 0xFF
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
    EQUIPEMENT_TYPE_WEAPON,
    EQUIPEMENT_TYPE_ARMOR,
    EQUIPEMENT_TYPE_BOOTS,
    EQUIPEMENT_TYPE_ACCESSORY
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

typedef enum
{
    CALENDAR_TIME_LATE_NIGHT1,
    CALENDAR_TIME_EARLY_MORNING,
    CALENDAR_TIME_MORNING,
    CALENDAR_TIME_LUNCH,
    CALENDAR_TIME_AFTERNOON,
    CALENDAR_TIME_AFTER_SCHOOL,
    CALENDAR_TIME_EVENING,
    CALENDAR_TIME_LATE_NIGHT2,
    CALENDAR_TIME_DARK_HOUR
} CalendarTime;

typedef enum
{
    CALENDAR_MONTH_JANUARY = 1,
    CALENDAR_MONTH_FEBRUARY,
    CALENDAR_MONTH_MARCH,
    CALENDAR_MONTH_APRIL,
    CALENDAR_MONTH_MAY,
    CALENDAR_MONTH_JUNE,
    CALENDAR_MONTH_JULY,
    CALENDAR_MONTH_AUGUST,
    CALENDAR_MONTH_SEPTEMBER,
    CALENDAR_MONTH_OCTOBER,
    CALENDAR_MONTH_NOVEMBER,
    CALENDAR_MONTH_DECEMBER
} CalendarMonths;

typedef enum
{
    CALENDAR_DAY_SUNDAY,
    CALENDAR_DAY_MONDAY,
    CALENDAR_DAY_TUESDAY,
    CALENDAR_DAY_WEDNESDAY,
    CALENDAR_DAY_THURSDAY,
    CALENDAR_DAY_FRIDAY,
    CALENDAR_DAY_SATURDAY,
    CALENDAR_DAY_MAX
} CalendarDays;

// 10 bytes
typedef struct
{
    u8 level;
    u16 health;
    u16 sp;
    u32 flags;   // See BATTLE_FLAG_*
    u8 aiTactic; // See enum AiTactic
} BattleStatus;

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

// 15 bytes
typedef struct
{
    u16 sUnk1;
    u16 id;
    u16 sUnk2;
    BattleStatus battleStatus;
} CharacterHeader; 

// 52 bytes, not sure of the real size
typedef struct
{
    u16 flags;
    u16 id;
    u8 level;
    u8 unkData1[0x03];
    u32 nextExp;   // For characters other than HERO, their exp is linked to their persona
    u16 skills[8]; // See enum PersonaSkills
    u8 stats[5];   // See enum PersonaStats
    u8 stats2[5];  // ??
    u8 stats3[5];  // ??
    // other data ?
} PersonaData; // For reference: Yukari = 008340ec

// 20 bytes
typedef struct 
{
    u16 id;
    u32 type;
    u16 sUnk1;
    u16 firstStat;
    u16 secondStat;
    u16 sUnk2;
    u8 unkData[0x04];
} EquipementData;

// 16 bytes
typedef struct
{
    u16 equipementsIdx[4];       // See enum EquipementTypes to access each idx
    EquipementData* equipements; // 00836794 -> 010c15f0
    void* unkPtr;                // 00836798 -> 010c2d90
} PlayerEquipementData;

// start: 00836224. 
typedef struct
{
    /*0x00*/ CharacterHeader character;
    /*0x10*/ u8 pad1[0x2B];
    /*0x3B*/ SocialStats socialStats;
    /*0x41*/ u32 nextExp;
    /*0x45*/ PhysicalState physicalState;
    /*0x4B*/ u16 activeSocialLink;
    /*0x4D*/ u8 socialLinkStat[0x1D];
             u8 unkData[0x982];
             u16 equippedPersona;      // 0 to 11
             PersonaData personas[12]; // start: 00836ba8
             u8 unkData2[0x292];
             PlayerEquipementData equipementsData; // 0083678c
             PersonaData compendium[188]; // 00836E52. Not in this struct (will move it later). Not sure of the size
    // TODO: The rest of the struct
} PlayerData;

// 868 bytes
typedef struct
{
    CharacterHeader character;
    SocialStats socialStats;
    u8 unkData1[0x06];
    PhysicalState physicalState;
    u16 equipementsIdx[4];         // always 0, 1, 2, 3
    EquipementData equipements[4];
    u8 unkData2[0x4C];
    PersonaData persona;
    u8 unkData3[0x297]; // TODO
} CharacterData;

typedef struct
{
    u16 daysSinceApr5; // 0083679c
    u8 time;
    // TODO: unk data after time
} CalendarData;

extern CalendarData calendar;
extern PlayerData gPlayerData;
extern CharacterData* characters[MAX_CHARACTERS];

void Game_SetScenarioMode(u32 scenario);
u32 Game_GetScenarioMode();

void FUN_0016f3e0(u32 idx, u32 value);
void FUN_0016cdf0(u16 characterId);

u16 Calendar_GetDaysSinceApr5();
u8 Calendar_GetTime();
void Calendar_SetTime(u8 time);

CharacterHeader* Character_GetCharacterHeader(u16 characterId);
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

u16 Character_GetEquipementIdx(u16 characterId, u16 equipementType);
u16 Character_GetEquipementId(u16 characterId, u16 equipementIdx);

u16 Player_GetActiveSocialLink();
u8 Player_GetSocialLinkLevel(u16 socialLink);
PersonaData* Player_GetPersonaByCompendiumIdx(u32 idx);

u32 Calendar_GetDaysSinceStartFromDate(u32 month, u32 day);
u32 Calendar_GetWeekDay(u32 daysSinceApr5);
u32 Calendar_GetCurrentWeekDay();
u8 Calendar_IsDateInRange(u32 startMonth, u32 startDay, u32 endMonth, u32 endDay);
u8 Calendar_IsDateInRangeFromDate(u32 monthToTest, u32 dayToTest, u32 startMonth, u32 startDay, u32 endMonth, u32 endDay);
u8 Calendar_IsDateInRangeFromStart(u32 month, u32 day, u32 range);

const u8* gData_getCourageLevelString(u16 idx);
const u8* gData_getCharmLevelString(u16 idx);
const u8* gData_getAcademicLevelString(u16 idx);

void P3FES_ASSERT(const u8* file, const u32 line);
void P3FES_LOG1(const char* fmt, ...);

#endif // G_DATA_H