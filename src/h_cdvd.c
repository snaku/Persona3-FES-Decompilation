#include "h_cdvd.h"
#include "h_dbprt.h"
#include "rw/rwplcore.h"
#include "temporary.h"

static HCdvd sCdvdListHead;        // 007e0380. Dummy head
static HCdvdCache sCdvdCache[256]; // 007d6f80

void H_Cdvd_BuildVolumePaths(const char* path, char* fileNameDst, char* dirDst);

// FUN_001007f0
void H_Cdvd_001007f0()
{
    // stub
}

// FUN_00100980. Asynchronous read
void H_Cdvd_Read()
{
    // TODO
}

// FUN_00100d80
HCdvd* H_Cdvd_Request(const char* path, u32 fileMode)
{
    HCdvd* curr;
    HCdvd* cdvd;
    char uppercasePath[256];

    H_Dbprt_FmtLog("REQ CDVD %s", path);

    curr = sCdvdListHead.next;

    H_Cdvd_BuildPathUppercase(path, uppercasePath);

    if (sCdvdListHead.next != NULL)
    {
        while (true)
        {
            if (strcmp(uppercasePath, curr->path) == 0)
            {
                curr->refCount++;
                return curr;
            }

            if (curr->next != NULL)
            {
                curr = curr->next;
            }
            else
            {
                break;
            }
        }
    }

    cdvd = RwCalloc(1, sizeof(HCdvd), rwMEMHINTDUR_GLOBAL);

    H_Cdvd_BuildPathUppercase(path, cdvd->path);
    H_Cdvd_BuildVolumePaths(cdvd->path, cdvd->fileName, cdvd->dir);

    cdvd->readState = 0;
    curr->next = cdvd;
    cdvd->next = NULL;
    cdvd->fileMemory = NULL;
    cdvd->unk_08 = 0;
    cdvd->fileMode = fileMode;
    cdvd->refCount = 1;
    cdvd->adxf = NULL;

    return cdvd;
}

// FUN_00100ec0
u8 H_Cdvd_Destroy(HCdvd* cdvd)
{
    // TODO

    return true;
}

// FUN_00101010
void H_Cdvd_BuildPathUppercase(const char* src, char* dst)
{
    // Need to rework a little bit

    char* pathBase;
    size_t basePathLen;
    char* dstPtr;
    u32 i;
    char currChar;

    pathBase = "VOL:\\";
    strcpy(src, pathBase);
    basePathLen = strlen(pathBase);

    dstPtr = dst + basePathLen;
    i = 0;
    while (i < 256)
    {
        currChar = src[i];
        if (currChar == '\0')
        {
            dstPtr[i] = '\0';
            return;
        }

        if (currChar == '/')
        {
            dstPtr[i] = '\\';
        }
        else if (currChar >= 'a' && currChar <= 'z')
        {
            dstPtr[i] = currChar - 0x20; // to upper
        }
        else
        {
            dstPtr[i] = currChar;
        }

        i++;
    }
}

// FUN_00101240
void H_Cdvd_BuildVolumePaths(const char* path, char* fileNameDst, char* dirDst)
{
    // TODO
}

// FUN_001013f0
void H_Cdvd_NormalizePath(const char* src, char* dst)
{
    // TODO
}

// FUN_001016b0
u32 H_Cdvd_IsFileLoaded(HCdvd* cdvd)
{
    return cdvd->readState == 4;
}

// FUN_00102100. Get file memory of a specific file in an archive (.PAC, .PAK or .BIN)
void* H_Cdvd_ArchiveGetFile(HCdvd* cdvd, s32 fileIdx, u32* fileSize)
{
    ArchiveEntryHeader entryHeader;
    uintptr_t fileMemoryAddr;
    s32 alignedSize;
    s32 i;

    fileMemoryAddr = (uintptr_t)cdvd->fileMemory;
    for (i = 0; i < fileIdx; i++)
    {
        memcpy(&entryHeader, (void*)fileMemoryAddr, sizeof(ArchiveEntryHeader));

        fileMemoryAddr += sizeof(ArchiveEntryHeader);

        alignedSize = entryHeader.fileSize + 0x3f;
        alignedSize /= 0x40;
        
        fileMemoryAddr += (alignedSize * 0x40);
    }

    memcpy(&entryHeader, (void*)fileMemoryAddr, sizeof(ArchiveEntryHeader));
    *fileSize = entryHeader.fileSize;

    return (void*)(fileMemoryAddr + sizeof(ArchiveEntryHeader));
}

// FUN_001021c0
void* H_Cdvd_CacheFindFile(const char* path, u32* fileSize)
{
    char uppercasePath[256];
    char normalizedPath[256];
    char cacheNormalizedPath[256];
    s32 i;

    if (path == (char*)1)
    {
        return NULL;
    }

    H_Cdvd_BuildPathUppercase(path, uppercasePath);
    H_Cdvd_NormalizePath(uppercasePath, normalizedPath);

    for (i = 0; i < 256; i++)
    {
        if (sCdvdCache[i].isValid)
        {
            H_Cdvd_NormalizePath(sCdvdCache[i].path, cacheNormalizedPath);

            if (strcmp(cacheNormalizedPath, normalizedPath) == 0)
            {
                *fileSize = sCdvdCache[i].fileSize;
                return sCdvdCache[i].fileMemory;
            }
        }
    }

    return NULL;
}

// FUN_001023a0. Synchronous read
void H_Cdvd_ReadSync(HCdvd* cdvd)
{
    while (true)
    {
        if (!H_Cdvd_IsFileLoaded(cdvd))
        {
            H_Cdvd_Read();
        }
        else
        {
            break;
        }
    }
}

// FUN_00102650
void H_Cdvd_CacheAdd(HCdvd* cdvd, void* fileMemory, u32 fileSize, const char* path)
{
    s32 i;
    HCdvdCache* curr;
    HCdvdCache* cache;

    i = 0;
    cache = sCdvdCache; // regswap (t2 instead of t1)
    for (; i < 256; i++)
    {
        curr = &cache[i];

        if (!curr->isValid)
        {
            curr->isValid = true;
            sCdvdCache[i].cdvd = cdvd;
            sCdvdCache[i].fileMemory = fileMemory;
            sCdvdCache[i].fileSize = fileSize;
            sCdvdCache[i].unk_110 = 0;
            memcpy(&sCdvdCache[i].path, path, 128);

            return;
        }
    }
}

// FUN_00102870
void H_Cdvd_CacheRemove(HCdvd* cdvd)
{
    s32 i;
    HCdvdCache* cache;
    HCdvdCache* curr;

    i = 0;
    cache = sCdvdCache;
    for (; i < 256; i++)
    {
        curr = &cache[i];

        if (curr->isValid && curr->cdvd == cdvd)
        {
            curr->isValid = false;
        }
    }
}