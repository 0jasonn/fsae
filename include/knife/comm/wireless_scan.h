#ifndef KNIFE_COMM_WIRELESS_SCAN_H
#define KNIFE_COMM_WIRELESS_SCAN_H

#include "types.h"
#include "sdk/wm/wm_standard.h"

// SDK call and handleResult names used by the WirelessManager scan and entry functions
// (startScan 0x020912a4, setEntry 0x02091d84, update_scan 0x02092ad8).
extern char data_0211b180[]; // name passed to handleResult after WM_SetEntry
extern char data_0211b10c[]; // name passed to handleResult after WM_StartScanEx (startScan)
extern char data_0211b1cc[]; // name passed to handleResult after WM_EndScan
extern char data_0211b1d8[]; // name passed to handleResult after WM_StartScanEx (update_scan)

#endif
