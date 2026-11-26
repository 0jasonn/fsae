#include "engine/functions.h"
#include "global.h"
#include "ui/widget/menu.h"

// Clears the nine cells (four halfwords each) and the three bytes and two halfwords after them.
void Menu_ClearCells(MenuCellWork *work) {
    s32 i;

    work->flag48 = 0;
    work->flag49 = 0;
    work->flag4a = 0;
    work->h4c = 0;
    work->h4e = 0;
    for (i = 0; i < 9; i++) {
        work->cells[i].f4 = 0;
        work->cells[i].f6 = 0;
        work->cells[i].f0 = 0;
        work->cells[i].f2 = 0;
    }
}

// Starts the touch panel auto sampling into samples (9 entries) with the calibration of the user info, then waits for the request to finish.
void Menu_StartTouch(TpSample *samples) {
    TpCalibrateParam calibrate;

    TP_Init();
    if (TP_GetUserInfo(&calibrate) != 0) {
        TP_SetCalibrateParam(&calibrate);
    }
    TP_RequestAutoSamplingStartAsync(0, 4, samples, 9);
    TP_WaitBusy(2);
    TP_CheckError(2);
}
