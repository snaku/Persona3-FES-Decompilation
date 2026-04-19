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
    s16 equippedPersona;         // 0 to 11
    DatPersonaWork personas[12];
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
    DatUnit unit;
    SocialStats socialStats;
    u8 unkData1[0x06];
    PhysicalState physicalState;
    u16 equipmentsIdx[4];         // always 0, 1, 2, 3
    EquipmentData equipments[4];
    u8 unkData2[0x4C];
    DatPersonaWork persona;
    u8 unkData3[0x297]; // TODO
} CharacterData;

extern CharacterData gCharacters[CHARACTER_MAX - 1];

extern PlayerPersonaData gPlayerPersonaData;

void datSetScenarioMode(u32 scenario);
u32 datGetScenarioMode();

void FUN_0016f3e0(u32 idx, u32 value);

DatUnit* datGetUnit(u16 characterId);
void datInitUnit(u16 characterId);
u8 datGetLevel(u16 characterId);
u16 datGetPersonaId(u16 characterId);
u32 datGetBadStatusNoDown(u16 characterId);
void datSetBadStatus(u16 characterId, u32 flags);
void datSetOldFatigueCounter(u16 characterId, u16 oldFatigueCounter);
void datClearBadStatus(u16 characterId, u32 flags);
u32 datGetExpUntilNextLevel(u16 characterId);
u8 datDidCharacterLevelUp(u16 characterId, u32 expGain);
void datSetAiTactic(u16 characterId, u8 aiTacticId);
u8 datGetAiTactic(u16 characterId);
void datSetPhysicalCondition(u16 characterId, u16 physicalCondition);
void datSetFatigueCounter(u16 characterId, u16 fatigueCounter);
void datSetHealth(u16 characterId, u16 health);
void datSetActiveSocialLink(u16 activeSocialLink);
u16 datGetDaysSinceApr5();
u8 datGetTime();
u16 datGetDaysSkipTarget();
u8 datGetTimeSkipTarget();
u32 datGetSkipToTarget();
void datSetAcademicPoint(u16 characterId, u16 academicPoint);
void datSetCharmPoint(u16 characterId, u16 charmPoint);
void datSetCouragePoint(u16 characterId, u16 couragePoint);
u16 datGetAcademicPoint(u16 characterId);
u16 datGetCharmPoint(u16 characterId);
u16 datGetCouragePoint(u16 characterId);
u16 datGetAcademicLevel(u16 academicPoint);
u16 datGetCharmLevel(u16 charmPoint);
u16 datGetCourageLevel(u16 couragePoint);
u32 datGetNextExp(u16 characterId);
u16 datGetPhysicalCondition(u16 characterId);
u16 datGetEquipmentIdx(u16 characterId, u16 equipmentType);
void datSetDaysSinceApr5(u16 daysSinceApr5);
void datSetTime(u8 time);
void datSetDaysSkipTarget(u16 days);
void datSetTimeSkipTarget(u8 time);
void datSetSkipToTarget(u32 val);
u8 datGetFlag(u32 bit);
void datSetFlag(u32 bit, u8 enabled);
void datClearFlagAll();
u16 datGetEquipmentId(u16 characterId, u16 equipmentIdx);
u8 datGetEquipmentEffect(u16 characterId, u16 equipmentIdx);
void datInitPersona(u32 characterId);
void datCompendiumInit();
u16 datGetActiveSocialLink();
u8 datGetSocialLinkLevel(u16 socialLink);
DatPersonaWork* datGetPersonaByCompendium(s32 idx);

#endif // G_DATA_H