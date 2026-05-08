#include "h_fade.h"
#include "kwln/kwlnTask.h"
#include "kwln/kwln.h"
#include "g_data.h"
#include "h_cdvd.h"

static s16 sFadeType;             // 007cdf08
static s16 sFadeCounter;          // 007cdf04
static s16 sFadeDuration;         // 007cdf00. In frames
static s16 sFadeState;            // 007cdefc
u8 sbssPad1[3];
static u8 sFadeRed;               // 007cdef8
u8 sbssPad2[3];
static u8 sFadeBlue;              // 007cdef4
u8 sbssPad3[3];
static u8 sFadeGreen;             // 007cdef0
static KwlnTask* sMaestroInTask;  // 007cdedc
static KwlnTask* sMaestroOutTask; // 007cded8
static u32 sFadeActive;           // 007cded4

static HCdvd* cdvds[8]; // 007e39d0

void H_Fade_Transition();
void H_Fade_001075b0();
void H_Fade_White();
void H_Fade_Day();
void H_Fade_Custom();

// FUN_00107060
void H_Fade_Main()
{
    RwRenderStateSet(rwRENDERSTATEZTESTENABLE, true);
    RwRenderStateSet(rwRENDERSTATESHADEMODE, rwSHADEMODEGOURAUD);
    RwRenderStateSet(rwRENDERSTATEZWRITEENABLE, true);
    RwRenderStateSet(rwRENDERSTATESRCBLEND, rwBLENDSRCALPHA);
    RwRenderStateSet(rwRENDERSTATEDESTBLEND, rwBLENDINVSRCALPHA);
    RwRenderStateSet(rwRENDERSTATETEXTUREFILTER, rwFILTERLINEAR);
    RwRenderStateSet(rwRENDERSTATEVERTEXALPHAENABLE, true);

    if (sFadeActive)
    {
        switch (sFadeType)
        {
            case HFADE_UNK0: // fallthrough
            case HFADE_TIME: // fallthrough
            case HFADE_AREA: // fallthrough
            case HFADE_UNK4: H_Fade_Transition(); break;

            case HFADE_UNK3: H_Fade_001075b0(); break;
            case HFADE_UNK5: H_Fade_001075b0(); break;

            case HFADE_WHITE:  H_Fade_White();  break;
            case HFADE_DAY:    H_Fade_Day();    break;
            case HFADE_CUSTOM: H_Fade_Custom();
        }
    }
}

// FUN_001071f0
void H_Fade_Transition()
{
    // TODO
}

// FUN_001075b0
void H_Fade_001075b0()
{
    // TODO
}

// FUN_001078a0
void H_Fade_White()
{
    // TODO
}

// FUN_00107b20
void H_Fade_Day()
{
    // TODO
}

// FUN_001081e0
void H_Fade_Custom()
{
    // TODO
}

// FUN_00108670
void H_Fade_SetType(s16 type)
{
    sFadeType = type;
}

// FUN_00108680
void H_Fade_SetCustomColor(u8 r, u8 g, u8 b)
{
    sFadeRed = r;
    sFadeGreen = g;
    sFadeBlue = b;
}

// FUN_001086a0
void H_Fade_SetDuration(s16 duration)
{
    sFadeDuration = duration;

    if (sFadeCounter > duration)
    {
        sFadeCounter = duration;
    }
}