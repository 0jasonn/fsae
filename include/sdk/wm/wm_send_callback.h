#ifndef SDK_WM_WM_SEND_CALLBACK_H
#define SDK_WM_WM_SEND_CALLBACK_H

#include "types.h"

// Argument of the port send callback of the data sharing (the SDK's WMPortSendCallback), only the fields the
// data sharing reads.
typedef struct WmPortSendCallback {
    /* 00 */ u16 apiid;
    /* 02 */ u16 errcode; // 0 on success, 10 when the send was dropped
    /* 04 */ u8 unk_04[6];
    /* 0a */ u16 port; // index of the port that sent
    /* 0c */ u8 unk_0c[0xe];
    /* 1a */ u16 sequence; // sequence number of the data set that was sent
    /* 1c */ u8 unk_1c[4];
    /* 20 */ void *sharing; // the work block that was passed when the data was queued
} WmPortSendCallback;

#endif
