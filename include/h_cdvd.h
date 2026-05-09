#ifndef H_CDVD_H
#define H_CDVD_H

#include "Utils.h"

// TODO: Create 'cri_adxf.h' file and create this struct
typedef struct ADX_FS ADX_FS;
typedef ADX_FS* ADXF;

#define HCDVD_FILENORMAL  0
#define HCDVD_FILEARCHIVE 1 // Is a .PAC, .PAK, .BIN or .FPC

typedef struct HCdvd HCdvd;

// 868 bytes
struct HCdvd
{
    HCdvd* prev;               // 0x00
    HCdvd* next;               // 0x04
    s32 unk_08;                // 0x08
    u32 readState;             // 0x0c
    char path[256];            // 0x10
    void* fileMemory;          // 0x110. 64 bytes aligned buffer of the file loaded in memory
    void* unalignedFileMemory; // 0x114. Unaligned buffer of the file loaded in memory
    u32 fileSize;              // 0x118. Size of the file in bytes
    u8 unkData1[0x34];
    u32 fileMode;              // 0x150. See 'H_CDVD_FILE*'
    ADXF adxf;                 // 0x154
    char fileName[256];        // 0x158
    char dir[256];             // 0x258
    s16 unk_358;
    s16 refCount;              // 0x35a
    u8 unkData3[0x08];
};

// 256 bytes. Header for an entry in an archive file (.PAC, .PAK or .BIN)
typedef struct ArchiveEntryHeader
{
    char fileName[252]; // 0x00
    u32 fileSize;       // 0xfc. Size in bytes
} ArchiveEntryHeader;

// 276 bytes
typedef struct HCdvdCache
{
    u32 isValid;      // 0x00
    HCdvd* cdvd;      // 0x04
    char path[128];   // 0x08
    void* fileMemory; // 0x88
    u32 fileSize;     // 0x8c
    u32 unk_110;      // 0x90
} HCdvdCache;

void H_Cdvd_Read();
HCdvd* H_Cdvd_Request(const char* path, u32 fileMode);
u8 H_Cdvd_Destroy(HCdvd* cdvd);
void H_Cdvd_BuildPathUppercase(const char* src, char* dst);
void H_Cdvd_NormalizePath(const char* src, char* dst);
u32 H_Cdvd_IsFileLoaded(HCdvd* cdvd);
void* H_Cdvd_ArchiveGetFile(HCdvd* cdvd, s32 fileIdx, u32* fileSize);
void* H_Cdvd_CacheFindFile(const char* path, u32* fileSize);
void H_Cdvd_ReadSync(HCdvd* cdvd);
void H_Cdvd_CacheAdd(HCdvd* cdvd, void* fileMemory, u32 fileSize, const char* path);
void H_Cdvd_CacheRemove(HCdvd* cdvd);

#endif