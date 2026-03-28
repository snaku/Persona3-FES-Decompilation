#ifndef H_CDVD_H
#define H_CDVD_H

#include "Utils.h"

#define MAX_PATH_SIZE 255

// TODO: Create 'cri_adxf.h' file and create this struct
typedef struct ADX_FS ADX_FS;
typedef ADX_FS* ADXF;

#define H_CDVD_FILENORMAL  0
#define H_CDVD_FILEARCHIVE 1 // Is a .PAC, .PAK or .BIN

typedef struct H_Cdvd H_Cdvd;

// 868 bytes
struct H_Cdvd
{
    H_Cdvd* prev;              // 0x00
    H_Cdvd* next;              // 0x04
    s32 unk_08;                // 0x08
    u32 readState;             // 0x0c
    char path[MAX_PATH_SIZE];  // 0x10
    void* fileMemory;          // 0x110. 64 bytes aligned buffer of the file loaded in memory
    void* unalignedFileMemory; // 0x114. Unaligned buffer of the file loaded in memory
    u32 fileSize;              // 0x118. Size of the file in bytes
    u8 unkData1[0x34];
    u32 fileMode;              // 0x150. See 'H_CDVD_FILE*'
    ADXF adxf;                 // 0x154
    u8 unkData2[0x202];
    u16 refCount;              // 0x35a
    u8 unkData3[0x08];
};

// 256 bytes. Header for an entry in an archive file (.PAC, .PAK or .BIN)
typedef struct ArchiveEntryHeader
{
    char fileName[252]; // 0x00
    u32 fileSize;       // 0xfc. Size in bytes
} ArchiveEntryHeader;

void H_Cdvd_AsyncRead();
H_Cdvd* H_Cdvd_Request(const char* path, u32 fileMode);
u8 H_Cdvd_Destroy(H_Cdvd* cdvd);
void H_Cdvd_BuildPathUppercase(char* src, char* dst);
u8 H_Cdvd_IsFileLoaded(H_Cdvd* cdvd);
void* H_Cdvd_GetFileMemoryInArchive(H_Cdvd* cdvd, s32 fileIdx, u32* fileSize);
void H_Cdvd_SyncRead(H_Cdvd* cdvd);

#endif