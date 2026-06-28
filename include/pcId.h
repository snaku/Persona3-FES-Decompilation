#ifndef PCID_H
#define PCID_H

#define IS_HERO(pcId) ((pcId) == PC_HERO)

typedef enum
{
    PC_NONE,
    PC_HERO,
    PC_YUKARI,
    PC_AIGIS,
    PC_MITSURU,
    PC_JUNPEI,
    PC_FUUKA,
    PC_AKIHIKO,
    PC_KEN,
    PC_SHINJIRO_OR_METIS, // Shinjiro if playing The Journey, Metis if The Answer
    PC_KOROMARU,
    PC_MAX
} PcId;

#endif