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
    u8 unkData1[0x08];
    char path[MAX_PATH_SIZE]; // 0x10
    void* fileMemory;         // 0x110. File loaded in memory
    void* unk_114;            // 0x114
    u32 fileSize;             // 0x118. Size of the file in bytes
    u8 unkData2[0x248];
};

H_Cdvd* H_Cdvd_Request(const char* path, u32 param_2);
void H_Cdvd_BuildPathUppercase(char* src, char* dst);

#endif