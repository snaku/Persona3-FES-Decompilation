#ifndef K_MINORIDS_H
#define K_MINORIDS_H

// Enum to use with 'FLD_MAJOR_THEBEL' (major id 21)
typedef enum
{
    FLD_MINOR_THEBEL_NORMAL,
    FLD_MINOR_THEBEL_FINAL = 50
} FldMinorIdThebel;

// Enum to use with 'FLD_MAJOR_ARQA' (major id 22)
typedef enum
{
    FLD_MINOR_ARQA_NORMAL,
    FLD_MINOR_ARQA_FINAL = 51
} FldMinorIdArqa;

// Enum to use with 'FLD_MAJOR_DUNGEON' (major id 32)
typedef enum
{
    FLD_MINOR_DUNGEON_ENTRANCE = 1,        // Entrance of tartarus
    FLD_MINOR_DUNGEON_FIRST_FLOOR,         // First floor of tartarus
    FLD_MINOR_DUNGEON_FIRST_FLOOR_DBG1,    // Debug version of first floor (no collision, no velvet room door etc)
    FLD_MINOR_DUNGEON_LAST_FLOOR_BETA = 5, // Seems like a beta version of the last floor. Not sure
    FLD_MINOR_DUNGEON_ROOFTOP,             // Rooftop of tartarus (where player finds Nyx)
    FLD_MINOR_DUNGEON_CRUCIFIXION,         // Where SEES gets betrayed by Ikutsuki and crucified
    FLD_MINOR_DUNGEON_ENTRANCE_CS,         // Cutscene version of tartarus entrance. Used when SEES gets betrayed by Ikutsuki
    FLD_MINOR_DUNGEON_FIRST_FLOOR_DBG2,    // Same as the first debug version, but with a Velvet room door and Mitsuru's bike
} FldMinorIdDungeon;

// Enum to use with 'FLD_MAJOR_THEBEL_BOSS' (major id 51)
typedef enum
{
    // TODO
    FLD_MINOR_THEBEL_BOSS_1,
} FldMinorIdThebelBoss;

// Enum to use with 'FLD_MAJOR_ARQA_BOSS' (major id 52)
typedef enum
{
    // TODO
    FLD_MINOR_ARQA_BOSS_1
} FldMinorIdArqaBoss;

#endif