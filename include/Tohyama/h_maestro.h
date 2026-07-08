#ifndef H_MAESTRO_H
#define H_MAESTRO_H

#include "Utils.h"
#include "rw/rwplcore.h"

typedef struct HCdvd HCdvd;
typedef struct KwlnTask KwlnTask;

typedef struct RwStream RwStream;
typedef struct Rt2dMaestro Rt2dMaestro;
typedef struct Rt2dObject Rt2dObject;   // TODO: create 'rt2d.h' file

typedef enum
{
    HMAESTRO_STATE_INITCDVD,
    HMAESTRO_STATE_INITSTREAM,
    HMAESTRO_STATE_INITSCENE,
    HMAESTRO_STATE_IDLE,
    HMAESTRO_STATE_DRAW,
    HMAESTRO_STATE_IDLE2
} HMaestroState;

// 308 bytes
typedef struct HMaestro
{
    s32 state;            // 0x00. See enum 'HMaestroState'
    HCdvd* cdvd;          // 0x04
    RwStream* rws;        // 0x08
    Rt2dMaestro* maestro; // 0x0c
    Rt2dObject* scene;    // 0x10
    f32 deltaTime;        // 0x14
    char path[256];       // 0x18
    u32 shouldLoop;       // 0x118
    u32 noDeltaTime;      // 0x11c
    u8 unkData1[0x08];
    f32 alphaMult;        // 0x128
    u32 useCdvd;          // 0x12c. Request cdvd or not
    s32 unk_130;          // 0x130
} HMaestro;

KwlnTask* H_Maestro_CreateTask(KwlnTask* parent, u32 priority, const char* path);
void H_Maestro_SetAlphaMult(KwlnTask* hmaestroTask, f32 alphaMult);
u32 H_Maestro_00111cb0(KwlnTask* hmaestroTask);
u32 H_Maestro_FinishedInit(KwlnTask* hmaestroTask);
void H_Maestro_RequestDraw(KwlnTask* hmaestroTask);
void H_Maestro_SetShouldLoop(KwlnTask* hmaestroTask, u32 shouldLoop);
void H_Maestro_00111f20(KwlnTask* hmaestroTask, u32 param_2);

#endif