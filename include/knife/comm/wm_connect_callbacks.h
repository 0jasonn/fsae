#ifndef KNIFE_COMM_WM_CONNECT_CALLBACKS_H
#define KNIFE_COMM_WM_CONNECT_CALLBACKS_H

#include "types.h"
#include "knife/comm/wm_work.h"

// Layouts of the SDK callback results the connect callbacks read (WMStartConnectCallback and WMStartMPCallback): the API
// id and error code come first (WmCallbackHead), the event kind follows.
typedef struct WmConnectResult {
    u16 apiId;
    u16 errCode;
    u8 unk_4[4];
    u16 kind;   // 0x08: WM state code (6, 7, 9 or 0x1a)
    u8 unk_0a[2];
    u16 param;  // 0x0c: parameter of the event (the disconnect reason for kind 9)
} WmConnectResult;

typedef struct WmStartMPResult {
    u16 apiId;
    u16 errCode;
    u16 kind;   // 0x04: 10 once the MP session is up
} WmStartMPResult;

extern char data_0211b284[]; // name passed to handleResult after WM_StartDataSharing

extern "C" {
void Knife_Comm_WirelessManager_callback_WM_StartConnect(void *result);
void Knife_Comm_WirelessManager_callback_WM_StartMP(void *result);
}

#endif
