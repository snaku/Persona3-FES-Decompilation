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
    u8 unkData2[0x255];
};

void H_Cdvd_BuildPathUppercase(char* srcBuf, char* dstBuf);

#endif