#ifndef K_MINORIDS_H
#define K_MINORIDS_H

// Enum to use with 'FIELD_MAJOR_ID_THEBEL' (major id 21)
typedef enum
{
    FIELD_MINOR_ID_THEBEL_NORMAL,
    FIELD_MINOR_ID_THEBEL_FINAL = 50
} FieldMinorIdThebel;

// Enum to use with 'FIELD_MAJOR_ID_ARQA' (major id 22)
typedef enum
{
    FIELD_MINOR_ID_ARQA_NORMAL,
    FIELD_MINOR_ID_ARQA_FINAL = 51
} FieldMinorIdArqa;

// Enum to use with 'FIELD_MAJOR_ID_DUNGEON' (major id 32)
typedef enum
{
    FIELD_MINOR_ID_DUNGEON_ENTRANCE = 1,        // Entrance of tartarus
    FIELD_MINOR_ID_DUNGEON_FIRST_FLOOR,         // First floor of tartarus
    FIELD_MINOR_ID_DUNGEON_FIRST_FLOOR_DBG1,    // Debug version of first floor (no collision, no velvet room door etc)
    FIELD_MINOR_ID_DUNGEON_LAST_FLOOR_BETA = 5, // Seems like a beta version of the last floor. Not sure
    FIELD_MINOR_ID_DUNGEON_ROOFTOP,             // Rooftop of tartarus (where player finds Nyx)
    FIELD_MINOR_ID_DUNGEON_CRUCIFIXION,         // Where SEES gets betrayed by Ikutsuki and crucified
    FIELD_MINOR_ID_DUNGEON_ENTRANCE_CS,         // Cutscene version of tartarus entrance. Used when SEES gets betrayed by Ikutsuki
    FIELD_MINOR_ID_DUNGEON_FIRST_FLOOR_DBG2,    // Same as the first debug version, but with a Velvet room door and Mitsuru's bike
} FieldMinorIdDungeon;

// Enum to use with 'FIELD_MAJOR_ID_THEBEL_BOSS' (major id 51)
typedef enum
{
    // TODO
    FIELD_MINOR_ID_THEBEL_BOSS_1,
} FieldMinorIdThebelBoss;

// Enum to use with 'FIELD_MAJOR_ID_ARQA_BOSS' (major id 52)
typedef enum
{
    // TODO
    FIELD_MINOR_ID_ARQA_BOSS_1
} FieldMinorIdArqaBoss;

#endif