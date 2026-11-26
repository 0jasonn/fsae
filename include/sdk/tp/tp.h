#ifndef SDK_TP_TP_H
#define SDK_TP_TP_H

// TwlSDK touch panel library: requests to the ARM7 touch panel service over the PXI FIFO (tag 6).
#include "types.h"

typedef void (*TpCallback)(u32 command, u32 result, u32 arg);

// Calibration points as given to TP_SetCalibrateParam (TP_GetUserInfo builds them from the firmware user data).
typedef struct TpCalibrateParam {
    s16 x0;       // 0x0
    s16 y0;       // 0x2
    s16 xDotSize; // 0x4
    s16 yDotSize; // 0x6
} TpCalibrateParam;

// One touch sample as stored in the auto-sampling buffer: 12-bit x and y, touch flag and validity.
typedef struct TpSample {
    u16 x;
    u16 y;
    u16 touch;
    u16 validity;
} TpSample;

// Calibration constants derived from TpCalibrateParam (TpWork.calibration; dsd names it data_0212b900).
typedef struct TpCalibration {
    s32 x0;       // 0x00
    s32 xDotSize; // 0x04
    s32 xScale;   // 0x08: fixed-point reciprocal computed by the hardware divider
    s32 y0;       // 0x0c
    s32 yDotSize; // 0x10
    s32 yScale;   // 0x14
} TpCalibration;

// Touch panel library state at data_0212b8e4 (0x3c bytes).
typedef struct TpWork {
    u16 initialized;           // 0x00
    u16 pad_02;                // 0x02
    TpCallback callback;       // 0x04
    u16 rawSample[4];          // 0x08: latest single sample (x, y, touch, validity)
    u16 latestIndex;           // 0x10: index of the newest entry in the auto-sampling buffer
    u16 frequency;             // 0x12: sampling frequency in scanlines
    TpSample *buffer;          // 0x14: auto-sampling ring buffer
    u16 bufferSize;            // 0x18
    u8 unk_1a[2];              // 0x1a
    TpCalibration calibration; // 0x1c
    u16 calibrated;            // 0x34
    u16 sampleState;           // 0x36
    u16 errorFlags;            // 0x38: bit per request that failed
    volatile u16 busyFlags;    // 0x3a: bit per request in flight
} TpWork;

extern TpWork data_0212b8e4;

extern "C" {
void TP_Init(void);
s32 TP_GetUserInfo(TpCalibrateParam *calibrate);
void TP_SetCalibrateParam(const TpCalibrateParam *calibrate);
void TP_RequestAutoSamplingStopAsync(void);
u32 TP_GetLatestIndexInAuto(void);
void TP_WaitBusy(s32 mask);
s32 TP_CheckError(s32 mask);

// Not decompiled yet.
void func_0201be6c(u32 tag, u32 data, s32 err); // PXI receive callback installed by TP_Init
void TP_RequestAutoSamplingStartAsync(u32 vCount, u32 frequency, TpSample *buffer, u32 bufferSize);
s32 TP_CalcCalibrateParam(TpCalibrateParam *calibrate, u16 x1, u16 y1, u16 dx1, u16 dy1, u16 x2, u16 y2, u16 dx2,
                          u16 dy2);
}

#endif
