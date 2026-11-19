#ifndef ENGINE_MESSAGE_REQUEST_H
#define ENGINE_MESSAGE_REQUEST_H

#include "types.h"

// Message request block (messageRequest, 0x18 bytes up to messageBox). MessageRequest() fills it from messageInitData
// and stores the text id; the scene code then waits for the phase to reach 6.
typedef struct MessageRequestWork {
    /* 00 */ u8 phase;     // low 7 bits: window phase (copied from messageBox.windowPhase, 6 = finished); 0x87 re-arms it
    /* 01 */ u8 unk_01[2];
    /* 03 */ u8 unk_03;    // low 5 bits set to 1 by the scene code before a message
    /* 04 */ u8 unk_04;    // low 5 bits: message kind chosen by the scene code (5, 7, 0xe, 0x10, npc script byte)
    /* 05 */ u8 width : 5; // width of the message box in cells
    /* 05 */ u8 unk_05 : 3;
    /* 06 */ u16 msgId;    // text id, set by MessageRequest()
    /* 08 */ u32 param;    // number shown in the message (score, player count)
    /* 0c */ u8 unk_0c[0x18 - 0x0c];
} MessageRequestWork;
extern MessageRequestWork messageRequest; // 0x0217d384

#endif
