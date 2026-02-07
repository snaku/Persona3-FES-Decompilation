#ifndef K_MAJORIDS_H
#define K_MAJORIDS_H

// Every major field ids. Use them with corresponding minor id enum in 'k_minorIds.h' file
typedef enum
{
    FIELD_MAJOR_ID_THEBEL = 21,      // 'Thebel' tartarus block (floor 2F to 16F). See enum 'FieldMinorIdThebel'
    FIELD_MAJOR_ID_ARQA,             // 'Arqa' tartarus block (floor 17F to 64F). See enum 'FieldMinorIdArqa'
    FIELD_MAJOR_ID_DUNGEON = 32,     // Tartarus related fields. See enum 'FieldMinorIdDungeon'
    FIELD_MAJOR_ID_THEBEL_BOSS = 51, // 'Thebel' tartarus block boss id. See enum 'FieldMinorIdThebelBoss'
    FIELD_MAJOR_ID_ARQA_BOSS,        // 'Arqa' tartarus block boss id. See enum 'FieldMinorIdArqaBoss'
} FieldMajorId;

#endif