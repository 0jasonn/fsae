#include "engine/functions.h"
#include "global.h"
#include "types.h"
#include "sdk/pxi/pxi_fifo.h"
#include "sdk/tp/tp.h"

// Hardware divider registers (0x04000280): control, 64-bit numerator and 64-bit denominator. The 32-bit result is read
// from 0x040002a0.
typedef struct DivRegs {
    volatile u16 control;
    u16 pad_02[7];
    volatile s32 numerator;
    volatile s32 numeratorHigh;
    volatile u64 denominator;
} DivRegs;

#define REG_DIV (*(DivRegs *)0x4000280)
#define REG_DIV_RESULT (*(volatile s32 *)0x40002a0)

// Shared system work holding the user calibration points read from the firmware (0x02fffc80).
typedef struct TpUserInfo {
    u8 unk_00[0x58];
    u16 x1;  // 0x58
    u16 y1;  // 0x5a
    u8 dx1;  // 0x5c
    u8 dy1;  // 0x5d
    u16 x2;  // 0x5e
    u16 y2;  // 0x60
    u8 dx2;  // 0x62
    u8 dy2;  // 0x63
} TpUserInfo;

// TP_Init() (0x0201c0e0): clears the state, waits for the ARM7 touch panel service and installs the receive callback.
void TP_Init(void) {
    if (data_0212b8e4.initialized != 0) {
        return;
    }
    data_0212b8e4.initialized = 1;
    Engine_Relay0201a070();
    data_0212b8e4.latestIndex = 0;
    data_0212b8e4.callback = NULL;
    data_0212b8e4.buffer = NULL;
    data_0212b8e4.sampleState = 0;
    data_0212b8e4.calibrated = 0;
    data_0212b8e4.busyFlags = 0;
    data_0212b8e4.errorFlags = 0;
    while (!PXI_IsCallbackReady(6, 1)) {
    }
    PXI_SetFifoRecvCallback(6, func_0201be6c);
}

// TP_GetUserInfo(calibrate) (0x0201c154): builds the calibration from the firmware user data; if there is none or it is
// inconsistent the parameters are cleared. Returns 1 either way.
s32 TP_GetUserInfo(TpCalibrateParam *calibrate) {
    TpUserInfo *info = (TpUserInfo *)0x2fffc80;
    u16 x1 = info->x1;
    u16 y1 = info->y1;
    u16 x2 = info->x2;
    u16 y2 = info->y2;
    u8 dx1 = info->dx1;
    u8 dy1 = info->dy1;
    u8 dx2 = info->dx2;
    u8 dy2 = info->dy2;

    if ((x1 == 0 && x2 == 0 && y1 == 0 && y2 == 0) ||
        TP_CalcCalibrateParam(calibrate, x1, y1, dx1, dy1, x2, y2, dx2, dy2) != 0) {
        calibrate->x0 = 0;
        calibrate->y0 = 0;
        calibrate->xDotSize = 0;
        calibrate->yDotSize = 0;
        return 1;
    }
    return 1;
}

// TP_SetCalibrateParam(calibrate) (0x0201c1e8): stores the calibration and precomputes the reciprocal dot sizes with the
// hardware divider; NULL disables calibration.
void TP_SetCalibrateParam(const TpCalibrateParam *calibrate) {
    u32 savedIrq;
    s32 dotSize;

    if (calibrate == NULL) {
        data_0212b8e4.calibrated = 0;
        return;
    }
    savedIrq = OS_DisableInterrupts();
    dotSize = calibrate->xDotSize;
    if (dotSize != 0) {
        REG_DIV.control = 0;
        REG_DIV.numerator = 0x10000000;
        REG_DIV.denominator = (u32)dotSize;
        data_0212b8e4.calibration.x0 = calibrate->x0;
        data_0212b8e4.calibration.xDotSize = dotSize;
        while (REG_DIV.control & 0x8000) {
        }
        data_0212b8e4.calibration.xScale = REG_DIV_RESULT;
    } else {
        data_0212b8e4.calibration.x0 = 0;
        data_0212b8e4.calibration.xDotSize = 0;
        data_0212b8e4.calibration.xScale = 0;
    }
    dotSize = calibrate->yDotSize;
    if (dotSize != 0) {
        REG_DIV.control = 0;
        REG_DIV.numerator = 0x10000000;
        REG_DIV.denominator = (u32)dotSize;
        data_0212b8e4.calibration.y0 = calibrate->y0;
        data_0212b8e4.calibration.yDotSize = dotSize;
        while (REG_DIV.control & 0x8000) {
        }
        data_0212b8e4.calibration.yScale = REG_DIV_RESULT;
    } else {
        data_0212b8e4.calibration.y0 = 0;
        data_0212b8e4.calibration.yDotSize = 0;
        data_0212b8e4.calibration.yScale = 0;
    }
    OS_RestoreInterrupts(savedIrq);
    data_0212b8e4.calibrated = 1;
}
