#ifndef SDK_WM_WM_DATASHARING_H
#define SDK_WM_WM_DATASHARING_H

#include "engine/functions.h"

// One shared data set: the bitmap of the stations whose data is present followed by their data.
typedef struct WmDataSet {
    /* 000 */ u16 receivedBitmap; // stations whose data has arrived
    /* 002 */ u16 sentBitmap;
    /* 004 */ u16 data[0xfe];
} WmDataSet;

// Work block of the data sharing (WM_StartDataSharing), 0x820 bytes
typedef struct WmDataSharing {
    /* 000 */ WmDataSet dataSets[4]; // ring of data sets
    /* 800 */ u16 sequence[4]; // per data set sequence number, 0xffff while empty
    /* 808 */ u16 writeIndex;
    /* 80a */ u16 sendIndex;
    /* 80c */ u16 readIndex;
    /* 80e */ u16 aidBitmap; // stations taking part
    /* 810 */ u16 dataLength; // bytes per station
    /* 812 */ u16 stationCount;
    /* 814 */ u16 dataSetLength; // stationCount * dataLength + 4
    /* 816 */ u16 port;
    /* 818 */ u16 doubleMode; // 1: two data sets are queued at start
    /* 81a */ u16 unk_81a;
    /* 81c */ u16 state; // 0 stopped, 1 running, 3 child running, 5 error
    /* 81e */ u16 unk_81e;
} WmDataSharing;

// Argument of the port receive callbacks (the SDK's WMPortRecvCallback), only the fields the data sharing reads.
typedef struct WmPortRecvCallback {
    /* 00 */ u16 apiid;
    /* 02 */ u16 errcode; // 0 on success
    /* 04 */ u16 state; // 0x15: data received; 7, 9 and 0x1a: parent notifications
    /* 06 */ u8 unk_06[6];
    /* 0c */ u16 *data; // received data
    /* 10 */ u16 length; // length of the received data
    /* 12 */ u16 aid; // station that sent the data / was disconnected
    /* 14 */ u8 unk_14[6];
    /* 1a */ u16 sequence;
    /* 1c */ WmDataSharing *sharing; // the work block that was passed to WM_SetPortCallback
    /* 20 */ void *unk_20;
} WmPortRecvCallback;

extern "C" {
// Queues data for sending through a port (the SDK's WM_SetMPDataToPortEx); parked, not matched yet.
s32 func_02020128(void *callback, void *arg, void *sendData, u16 sendDataSize, u16 destBitmap, u16 port, u16 priority);
s32 WM_EndDataSharing(void *buf); // src/sdk/wm/wm_datasharing_end.cpp
void WmDataSharingReceiveCallback_Parent(WmPortRecvCallback *callback);
void WmDataSharingStoreData(WmDataSharing *sharing, u16 aid, u16 *data); // 0x02020b84, called WmDataSharingStoreData
void WmDataSharingSendDataSet(WmDataSharing *sharing, s32 flag); // 0x02020c54
void WmDataSharingReceiveCallback_Child(WmPortRecvCallback *callback);
void WmDataSharingSetDataCallback(void *result);
}

#endif
