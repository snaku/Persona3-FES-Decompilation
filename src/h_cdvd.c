#include "h_cdvd.h"
#include "temporary.h"

static H_Cdvd sCdvdListHead; // 007e0380. Dummy head

// FUN_00100980. Asynchronous read
void H_Cdvd_AsyncRead()
{
    // TODO
}

// FUN_00100d80
H_Cdvd* H_Cdvd_Request(const char* path, u32 fileMode)
{
    // TODO

    return NULL;
}

// FUN_00100ec0
u8 H_Cdvd_Destroy(H_Cdvd* cdvd)
{
    // TODO

    return true;
}

// FUN_00101010
void H_Cdvd_BuildPathUppercase(char* src, char* dst)
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
    while (i < MAX_PATH_SIZE)
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

// FUN_001016b0
u8 H_Cdvd_IsFileLoaded(H_Cdvd* cdvd)
{
    return cdvd->readState == 4;
}

// FUN_00102100. Get file memory of a specific file in an archive (.PAC, .PAK or .BIN)
void* H_Cdvd_GetFileMemoryInArchive(H_Cdvd* cdvd, s32 fileIdx, u32* fileSize)
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
        alignedSize >>= 6;

        if (alignedSize < 0)
        {
            alignedSize += 0x3f;
            alignedSize >>= 6;
        }
        
        fileMemoryAddr += (alignedSize << 6);
    }

    memcpy(&entryHeader, (void*)fileMemoryAddr, sizeof(ArchiveEntryHeader));
    *fileSize = entryHeader.fileSize;

    return (void*)(fileMemoryAddr + sizeof(ArchiveEntryHeader));
}

// FUN_001023a0. Synchronous read
void H_Cdvd_SyncRead(H_Cdvd* cdvd)
{
    while (true)
    {
        if (!H_Cdvd_IsFileLoaded(cdvd))
        {
            H_Cdvd_AsyncRead();
        }
        else
        {
            break;
        }
    }
}