#include "Battle/btlCamera.h"
#include "Battle/battle.h"
#include "Battle/btlUnit.h"
#include "kwln/kwln.h"
#include "datUnit.h"

// FUN_002a38f0
void btlCameraSetState(u16 state, BtlAction* action, u32 param_3)
{
    // TODO
}

// FUN_002a3b00
u32 btlCameraUpdateSetStatePacket(void* work)
{
    BtlCameraPacketSetState* packet;

    packet = (BtlCameraPacketSetState*)work;

    btlCameraSetState(packet->state, packet->action, true);

    return true;
}

// FUN_002a3b40
BtlPacket* btlCameraCreateSetStatePacket(BtlAction* action, u16 state)
{
    BtlPacket* packet;
    BtlCameraPacketSetState* work;

    packet = btlPacketCreate(BTLCAMERA_PACKET_SETSTATE, sizeof(BtlCameraPacketSetState));

    packet->updateFunc = btlCameraUpdateSetStatePacket;

    work = (BtlCameraPacketSetState*)packet->workData;

    work->action = action;
    work->state = state;

    return packet;
}

// FUN_002a3ba0
u32 btlCameraUpdateMoveToPacket(void* work)
{
    // TODO

    return true;
}

// FUN_002a3d70
BtlPacket* btlCameraCreateMoveToPacket(BtlAction* action, 
                                       const RwV3d* startPos,
                                       const RwV3d* startTarget,
                                       const RwV3d* endPos,
                                       const RwV3d* endTarget,
                                       f32 duration)
{
    BtlPacket* packet;
    BtlCameraPacketMoveTo* work;

    packet = btlPacketCreate(BTLCAMERA_PACKET_MOVETO, sizeof(BtlCameraPacketMoveTo));

    packet->updateFunc = btlCameraUpdateMoveToPacket;

    work = (BtlCameraPacketMoveTo*)packet->workData;

    work->action = action;
    work->duration = duration;

    if (startPos != NULL && startTarget != NULL)
    {
        work->startPos = *startPos;
        work->startTarget = *startTarget;

        work->currPosAsStart = false;
    }
    else
    {
        work->currPosAsStart = true;
    }

    work->endPos = *endPos;
    work->endTarget = *endTarget;

    return packet;
}

// FUN_002a4330
void btlCameraCheckUnitFade()
{
    RwFrame* cameraFrame;
    RwMatrix* cameraMat;
    BtlUnitList* currUnitList;
    BtlUnit* currUnit;
    u16 i;
    RwV3d sphereCenter;
    RwV3d diff;

    cameraFrame = (RwFrame*)kwlnGetMainCamera()->object.object.parent;
    cameraMat = &cameraFrame->modelling;

    // PC and EC
    for (i = 0; i < UNIT_GENUS_PS; i++)
    {
        currUnitList = &gBtl->unitLists[i];
        currUnit = currUnitList->head;

        while (currUnit != NULL)
        {
            if (currUnit->flags3 & BTLUNIT_FLAG3_UNK08)
            {
                btlUnitGetSphereWorldCenter(currUnit, &sphereCenter);

                diff.x = cameraMat->pos.x - sphereCenter.x;
                diff.y = cameraMat->pos.y - sphereCenter.y;
                diff.z = cameraMat->pos.z - sphereCenter.z;

                if (RwV3dLength(&diff) <= (currUnit->sphereRadius * currUnit->scale) + 200.0f)
                {
                    btlUnitSetFlags(currUnit, BTLUNIT_FLAG_FADE);
                }
                else
                {
                    btlUnitClearFlags(currUnit, BTLUNIT_FLAG_FADE);
                }
            }

            currUnit = currUnit->next;
        }
    }
}