#include "engine/functions.h"
#include "global.h"
#include "types.h"
#include "game/com_sio.h"

// Functions in this file (module com, original names from the debug build):
//   func_020280e0 (dsd name, declared in functions.h), MachiukeStart (MachiukeStart()), MachiukeStop (MachiukeStop()),
//   ComMain (ComMain()), ComUpdate (ComUpdate()), func_020281a8 and func_020281ac (empty functions)

// Communication state block at data_0212c9a8 (see com.cpp for the first fields).
typedef struct ComWork {
    /* 00 */ u8 request;      // request code, index into data_020f258c in ComMain
    /* 01 */ u8 phase;
    /* 02 */ u8 unk_02[1];
    /* 03 */ u8 status;       // returned by func_020280e0, cleared by MachiukeStart and MachiukeStop
    /* 04 */ u32 requestFlag;
    /* 08 */ u32 finishArg;
    /* 0c */ u16 unk_0c;
    /* 0e */ u8 machiukeActive; // set to 1 by MachiukeStart
} ComWork;

#define COM_WORK ((ComWork *)data_0212c9a8)

extern u8 data_0212c9a8[];
extern u8 data_0212c9b8[];
extern u32 data_0212c544;
extern u32 opTitleState;
extern void (*const data_020f258c[])(void);

void ComStart(u8 request);

// func_020280e0 (0x020280e0): the status byte of the communication state.
ARM u32 func_020280e0(void) {
    return COM_WORK->status;
}

// MachiukeStart (0x020280f0): starts the serial, requests code 2 and sets the active flag.
ARM void MachiukeStart(void) {
    MultiSioInit();
    ComStart(2);
    COM_WORK->status = 0;
    COM_WORK->machiukeActive = 1;
}

// MachiukeStop (0x0202811c): restarts the serial with request 0 and clears the status.
ARM void MachiukeStop(void) {
    MultiSioInit();
    ComStart(0);
    COM_WORK->status = 0;
}

// ComMain (0x02028140): ORs opTitleState into data_0212c544, then calls the handler for the current request.
ARM void ComMain(void) {
    data_0212c544 |= opTitleState;
    data_020f258c[COM_WORK->request]();
}

// ComUpdate (0x02028184): sends the data block at data_0212c9b8 and clears its 0x34 bytes.
ARM void ComUpdate(void) {
    MultiSioSendDataSet(data_0212c9b8);
    func_02029a50(data_0212c9b8, 0x34);
}

// Empty functions (dsd names kept, plain symbols).
extern "C" void func_020281a8(void);
extern "C" void func_020281ac(void);

ARM void func_020281a8(void) {
}

ARM void func_020281ac(void) {
}
