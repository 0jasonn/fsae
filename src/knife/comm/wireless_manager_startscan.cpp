// functions.h still declares startScan with a void result (the original returns BOOL): hide that
// declaration until functions.h is corrected.
#define Knife_Comm_WirelessManager_startScan Knife_Comm_WirelessManager_startScan_void
#include "engine/functions.h"
#undef Knife_Comm_WirelessManager_startScan
#include "knife/comm/wireless_manager_methods.h"
#include "knife/comm/wireless_scan.h"

extern "C" {
void Knife_Comm_WirelessManager_callback_WM_StartScanEx(void *result);
void MI_CpuFill8(void *dst, u8 value, u32 size);
void MI_CpuCopy8(const void *src, void *dst, u32 size);
// the original returns BOOL (TRUE once the scan started), functions.h declares a void result
BOOL Knife_Comm_WirelessManager_startScan(void *self, BOOL scanMode, const u8 *bssid);
}

// Knife::Comm::WirelessManager::startScan(bool, unsigned char const*) (0x020912a4): from state 2 (idle) or 5 (scanning), with
// channels allowed, clears the scan parameter block (+0xcc0) and fills it (result buffer, 0x400 bytes, allowed channels,
// dispersion scan period, the given BSSID or broadcast, scan type 1), then starts WM_StartScanEx. On success the state
// becomes 4 (waiting for the scan to start) and the timer is cleared. Runs with interrupts disabled.
BOOL Knife_Comm_WirelessManager_startScan(void *self, BOOL scanMode, const u8 *bssid) {
    WmInterruptSection section;
    WirelessManagerWork *wm = (WirelessManagerWork *)self;

    if (wm->state != 2 && wm->state != 5) {
        return FALSE;
    }
    if (func_02090ecc(self) != 0) {
        return FALSE;
    }
    if (wm->channelMask == 0) {
        return FALSE;
    }
    MI_CpuFill8(&wm->scanParam, 0, 0x44);
    wm->scanParam.scanBuf = wm->buf2;
    wm->scanParam.scanBufSize = 0x400;
    wm->scanParam.channelList = wm->channelMask;
    wm->scanParam.maxChannelTime = WM_GetDispersionScanPeriod();
    if (bssid != NULL) {
        MI_CpuCopy8(bssid, wm->scanParam.bssid, 6);
    } else {
        MI_CpuFill8(wm->scanParam.bssid, 0xff, 6);
    }
    wm->scanParam.scanType = 1;
    wm->scanParam.ssidLength = 0;
    wm->scanMode = scanMode;
    if (!Knife_Comm_WirelessManager_handleResult(self, WM_StartScanEx((void *)Knife_Comm_WirelessManager_callback_WM_StartScanEx, &wm->scanParam), 0, data_0211b10c)) {
        return FALSE;
    }
    wm->state = 4;
    wm->timer = 0;
    wm->callPending = 1;
    return TRUE;
}
