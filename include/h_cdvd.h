#ifndef H_CDVD_H
#define H_CDVD_H

#include "Utils.h"

#define MAX_PATH_SIZE 255

typedef struct H_Cdvd H_Cdvd;

// 868 bytes
struct H_Cdvd
{
    H_Cdvd* prev;             // 0x00
    H_Cdvd* next;             // 0x04
    s32 unk_08;               // 0x08
    u32 state;                // 0x0c
    char path[MAX_PATH_SIZE]; // 0x10
    void* fileMemory;         // 0x110. File loaded in memory
    void* unk_114;            // 0x114
    u32 fileSize;             // 0x118. Size of the file in bytes
    u8 unkData2[0x248];
};

H_Cdvd* H_Cdvd_Request(const char* path, u32 param_2);
u8 H_Cdvd_Destroy(H_Cdvd* cdvd);
void H_Cdvd_BuildPathUppercase(char* src, char* dst);
u8 H_Cdvd_IsFileLoaded(H_Cdvd* cdvd);

#endif