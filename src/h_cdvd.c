#include "h_cdvd.h"
#include "temporary.h"

static H_Cdvd sCdvdListHead; // 007e0380. Dummy head

// FUN_00100d80
H_Cdvd* H_Cdvd_Request(const char* path, u32 param_2)
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