/*This file is horrible*/

#ifndef G_DATA_H
#define G_DATA_H

#include "datUnit.h"
#include "datPersona.h"
#include "datCalendar.h"
#include "pcId.h"
#include "g_flags.h"

#define MAX_CHARACTER_LEVEL 99

#define SOCIAL_STAT_MIN_POINT 0
#define SOCIAL_STAT_MAX_POINT 999

typedef enum
{
    SCENARIO_MODE_JOURNEY,
    SCENARIO_MODE_ANSWER
} ScenarioMode; 

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
typedef struct DatSocial
{
    u16 academicPoint;
    u16 charmPoint;
    u16 couragePoint;
} DatSocial;

// 6 bytes
typedef struct DatPhysical
{
    u16 physicalCondition; // See enum CharacterPhysicalCondition
    u16 fatigueCounter;    // if 0, character will become tired
    u16 oldFatigueCounter; // value before entering tartarus
} DatPhysical;

// 20 bytes
typedef struct DatEquipment
{
    u16 id;
    u32 type;
    u8 cUnk1;
    u8 effect;
    u16 firstStat;
    u16 secondStat;
    u16 sUnk2;
    u8 unkData[0x04];
} DatEquipment;

// 16 bytes
typedef struct DatHeroEquipment
{
    u16 equipmentsIdx[4];     // See enum EquipmentTypes to access each idx
    DatEquipment* equipments; // 00836794 -> 010c15f0
    void* unkPtr;             // 00836798 -> 010c2d90
} DatHeroEquipment;

typedef struct DatHeroPersona
{
    s16 equippedPersona;         // 0 to 11
    DatPersonaWork personas[12];
} DatHeroPersona;

typedef struct DatHeroStatus
{
    DatSocial socialStats;
    u32 nextExp;
    DatPhysical physicalState;
    u16 activeSocialLink;
    u8 socialLinkStat[29];
} DatHeroStatus;

// 868 bytes
typedef struct DatPc
{
    s32 unk_00;
    DatUnit unit;
    DatSocial socialStats;
    u8 unkData1[0x06];
    DatPhysical physicalState;
    u16 equipmentsIdx[4];         // always 0, 1, 2, 3
    DatEquipment equipments[4];
    u8 unkData2[0x4C];
    DatPersonaWork persona;
    u8 unkData3[0x297]; // TODO
} DatPc;

// at least 28064 bytes
typedef struct DatGlobal
{
    DatPc pcs[PC_MAX];              // 00833948
    DatUnit heroUnit;               // 00836224
    DatHeroStatus heroStatus;       // 00836260
    DatHeroEquipment heroEquip;     // 0083678c
    CalendarWork calendarWork;      // 0083679c
    DatHeroPersona heroPersona;     // 00836ba8
    DatPersonaWork compendium[256]; // 00836e1c
    u32 flags[FLG_ARR_SIZE];        // 0083a21c. See 'g_flags.h'
    u32 unk_0083a4dc[128];          // 0083a4dc
    u32 heroMoney;                  // 0083a6dc
    s16 partyIds[4];                // 0083a6e0
    // TODO: other data
} DatGlobal;

extern DatGlobal gGlobalWork;

void datSetScenarioMode(u32 scenario);
u32 datGetScenarioMode();

void FUN_0016f3e0(u32 idx, u32 value);

DatUnit* datGetUnit(s16 pcId);
void datInitUnit(u16 pcId);
u8 datGetLevel(u16 pcId);
u16 datGetPersonaId(u16 pcId);
u32 datGetBadStatusNoDown(u16 pcId);
void datSetBadStatus(u16 pcId, u32 flags);
void datSetOldFatigueCounter(u16 pcId, u16 oldFatigueCounter);
void datClearBadStatus(u16 pcId, u32 flags);
u32 datGetExpUntilNextLevel(u16 pcId);
u8 datDidCharacterLevelUp(u16 pcId, u32 expGain);
void datSetAiTactic(u16 pcId, u8 aiTacticId);
s16 datGetPartyId(s32 idx);
u8 datGetAiTactic(u16 pcId);
void datSetPhysicalCondition(u16 pcId, u16 physicalCondition);
void datSetFatigueCounter(u16 pcId, u16 fatigueCounter);
void datSetHp(u16 pcId, u16 hp);
void datSetActiveSocialLink(u16 activeSocialLink);
s16 datGetDaysSinceApr5();
s8 datGetTime();
s16 datGetDaysSkipTarget();
s8 datGetTimeSkipTarget();
u32 datGetSkipToTarget();
void datSetAcademicPoint(u16 pcId, u16 academicPoint);
void datSetCharmPoint(u16 pcId, u16 charmPoint);
void datSetCouragePoint(u16 pcId, u16 couragePoint);
u16 datGetAcademicPoint(u16 pcId);
u16 datGetCharmPoint(u16 pcId);
u16 datGetCouragePoint(u16 pcId);
u16 datGetAcademicLevel(u16 academicPoint);
u16 datGetCharmLevel(u16 charmPoint);
u16 datGetCourageLevel(u16 couragePoint);
u32 datGetNextExp(u16 pcId);
u16 datGetPhysicalCondition(u16 pcId);
u16 datGetEquipmentIdx(u16 pcId, u16 equipmentType);
void datSetDaysSinceApr5(s16 daysSinceApr5);
void datSetTime(s8 time);
void datSetDaysSkipTarget(s16 days);
void datSetTimeSkipTarget(s8 time);
void datSetSkipToTarget(u32 val);
u32 datGetFlag(s32 bit);
void datSetFlag(s32 bit, u8 enabled);
void datClearFlagAll();
u16 datGetEquipmentId(u16 pcId, u16 equipmentIdx);
u8 datGetEquipmentEffect(u16 pcId, u16 equipmentIdx);
void datInitPersona(u32 pcId);
void datCompendiumInit();
u16 datGetActiveSocialLink();
u8 datGetSocialLinkLevel(u16 socialLink);
DatPersonaWork* datGetPersonaByCompendium(s32 idx);

#endif // G_DATA_H