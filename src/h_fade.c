#include "h_fade.h"
#include "kwln/kwlnTask.h"
#include "kwln/kwln.h"
#include "g_data.h"
#include "h_cdvd.h"

static s16 sFadeType;             // 007cdf08
static s16 sFadeCounter;          // 007cdf04
static s16 sFadeDuration;         // 007cdf00. In frames
static s16 sFadeState;            // 007cdefc
static u8 sFadeRed;               // 007cdef8
u8 sbssPad1[3];
static u8 sFadeBlue;              // 007cdef4
u8 sbssPad1[3];
static u8 sFadeGreen;             // 007cdef0
static KwlnTask* sMaestroInTask;  // 007cdedc
static KwlnTask* sMaestroOutTask; // 007cded8
static u32 sFadeActive;           // 007cded4

static HCdvd* cdvds[8]; // 007e39d0

static void H_Fade_Anim();
static void H_Fade_Transition();
static void H_Fade_White();
static void H_Fade_Day();
static void H_Fade_Custom();

// FUN_00107020
void H_Fade_ReadPak()
{
    HCdvd* cdvd;

    cdvd = H_Cdvd_Request("camp/fade_pak.pak", HCDVD_FILEARCHIVE);
    cdvds[0] = cdvd;
    H_Cdvd_ReadSync(cdvd);
}

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
            case HFADE_ANMLR:   // fallthrough
            case HFADE_ANMTIME: // fallthrough
            case HFADE_ANMAREA: // fallthrough
            case HFADE_ANMMOVE: H_Fade_Anim(); break;

            case HFADE_TRANSITION:  H_Fade_Transition(); break;
            case HFADE_TRANSITION2: H_Fade_Transition(); break;

            case HFADE_WHITE:  H_Fade_White();  break;
            case HFADE_DAY:    H_Fade_Day();    break;
            case HFADE_CUSTOM: H_Fade_Custom();
        }
    }
}

// FUN_001071b0
void H_Fade_Clear()
{
    if (sFadeActive)
    {
        sFadeActive = false;

        if (sMaestroOutTask != NULL)
        {
            kwlnTaskDestroyWithHierarchy(sMaestroOutTask);
            sMaestroOutTask = NULL;
        }
    }
}

// FUN_001071f0
static void H_Fade_Anim()
{
    // TODO
}

// FUN_001075b0
static void H_Fade_Transition()
{
    // TODO
}

// FUN_001078a0
static void H_Fade_White()
{
    // TODO: fix stack frame size (the problem is caused by RwRenderStateSet)

    RwIm2DVertex vertices[4];
    f32 alpha;
    f32 recipZ;
    s16 i;
    f32 z;
    f32 col;

    RwRenderStateSet(rwRENDERSTATEZTESTENABLE, true);
    RwRenderStateSet(rwRENDERSTATESHADEMODE, rwSHADEMODEGOURAUD);
    RwRenderStateSet(rwRENDERSTATEZWRITEENABLE, true);
    RwRenderStateSet(rwRENDERSTATESRCBLEND, rwBLENDSRCALPHA);
    RwRenderStateSet(rwRENDERSTATEDESTBLEND, rwBLENDINVSRCALPHA);
    RwRenderStateSet(rwRENDERSTATETEXTUREFILTER, rwFILTERLINEAR);
    RwRenderStateSet(rwRENDERSTATEVERTEXALPHAENABLE, true);

    switch (sFadeState)
    {
        case HFADE_STATE_INIT_OUT:
            sFadeState = HFADE_STATE_OUT;
            sFadeCounter = 0;
            // fallthrough
        case HFADE_STATE_OUT:
            sFadeCounter++;
            if (sFadeCounter == sFadeDuration)
            {
                sFadeState = HFADE_STATE_HOLD;
            }
            break;

        case HFADE_STATE_HOLD: break;
        
        case HFADE_STATE_INIT_IN: 
            sFadeCounter = sFadeDuration;
            sFadeState = HFADE_STATE_IN;
            break;

        case HFADE_STATE_IN:
            sFadeCounter--;
            if (sFadeCounter == 0)
            {
                sFadeActive = false;
            }
    }

    recipZ = 1.0f / kwlnGetMainCamera()->nearPlane;
    alpha = (f32)((sFadeCounter * 255) / sFadeDuration);
    i = 0;
    z = RwIm2DGetNearScreenZ() - 100.0f;
    col = 255.0f; // TODO: lui v1, 0x437f here and not in the loop body
    for(; i < 4; i++)
    {
        vertices[i].u.els.scrVertex.z = z;
        vertices[i].u.els.recipZ = recipZ;

        vertices[i].u.els.color.r = col;
        vertices[i].u.els.color.g = col;
        vertices[i].u.els.color.b = col;
        vertices[i].u.els.color.a = alpha;
    }

    vertices[0].u.els.scrVertex.x = 0.0f;
    vertices[0].u.els.scrVertex.y = 0.0f;

    vertices[1].u.els.scrVertex.x = 640.0f;
    vertices[1].u.els.scrVertex.y = 0.0f;

    vertices[2].u.els.scrVertex.x = 0.0f;
    vertices[2].u.els.scrVertex.y = 448.0f;

    vertices[3].u.els.scrVertex.x = 640.0f;
    vertices[3].u.els.scrVertex.y = 448.0f;

    RwRenderStateSet(rwRENDERSTATETEXTURERASTER, NULL);
    RwIm2DRenderPrimitive(rwPRIMTYPETRISTRIP, vertices, 4);
}

// FUN_00107b20
static void H_Fade_Day()
{
    // TODO
}

// FUN_001081e0
static void H_Fade_Custom()
{
    // TODO
}

// FUN_00108570
u32 H_Fade_FadeOut()
{
    if (!sFadeActive)
    {
        sFadeDuration = 15;
        sFadeActive = true;
        sFadeState = HFADE_STATE_INIT_OUT;
        sFadeRed = 0;
        sFadeBlue = 0;
        sFadeGreen = 0;
        sFadeType = HFADE_ANMLR;
    }
    else
    {
        return false;
    }

    return sFadeActive;
}

// FUN_001085c0
u32 H_Fade_FadeIn()
{
    if (sFadeActive && sFadeState == HFADE_STATE_HOLD)
    {
        sFadeDuration = 15;
        sFadeActive = true;
        sFadeState = HFADE_STATE_INIT_IN;

        if (datGetTime() == CALENDAR_TIME_DARK_HOUR && datGetFlag(5138))
        {
            datSetFlag(5138, false);

            sFadeDuration = 40;
            sFadeCounter = 40;
            sFadeType = HFADE_DAY;
        }

        return true;
    }

    return false;
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

// FUN_001086d0. Same thing as 'H_Fade_IsFadeOutDone'
u32 H_Fade_IsHolding()
{
    if (sFadeActive && sFadeState == HFADE_STATE_HOLD)
    {
        return true;
    }

    return false;
}

// FUN_00108710. Same thing as 'H_Fade_IsHolding'
u32 H_Fade_IsFadeOutDone()
{
    if (sFadeActive)
    {
        return sFadeState == HFADE_STATE_HOLD;
    }

    return true;
}