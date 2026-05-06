#include "h_cursor.h"
#include "kwln/kwlnTask.h"
#include "kwln/kwln.h"

// FUN_00100230
void* H_Cursor_UpdateTask(KwlnTask* hcursorTask)
{
    // TODO

    return KWLNTASK_CONTINUE;
}

// FUN_00100570
u32 H_Cursor_GetShouldDraw(KwlnTask* hcursorTask)
{
    return ((HCursorWork*)hcursorTask->workData)->shouldDraw;
}

// FUN_00100580
void H_Cursor_DestroyTask(KwlnTask* hcursorTask)
{
    RwFree(hcursorTask->workData);
}

// FUN_001005b0
KwlnTask* H_Cursor_CreateTask(KwlnTask* parent, f32 zOffset, RwV2d pos, RwRect rect, RwRGBA color)
{
    HCursorWork* work;
    KwlnTask* task;
    RwRect _rect;

    _rect = rect;

    work = RwCalloc(1, sizeof(HCursorWork), rwMEMHINTDUR_GLOBAL);
    if (work == NULL)
    {
        return NULL;
    }

    task = kwlnTaskCreate(parent,
                          "H CURSOR Draw",
                          6335,
                          H_Cursor_UpdateTask,
                          H_Cursor_DestroyTask,
                          work);
    if (task == NULL)
    {
        return NULL;
    }

    work->zOffset = zOffset;
    work->pos = pos;
    work->rect = _rect;
    work->colors[0] = color;
    work->colors[1] = color;
    work->colors[2] = color;
    work->colors[3] = color;
    work->shouldDraw = true;

    return task;
}