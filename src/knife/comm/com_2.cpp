#include "engine/functions.h"
#include "global.h"
#include "types.h"
#include "knife/comm/com_sio.h"
#include "knife/comm/com_api.h"
#include "knife/comm/com.h"

// Functions in this file (module com, original names from the debug build):
//   func_020280e0 (dsd name, declared in functions.h), MachiukeStart (MachiukeStart()), MachiukeStop (MachiukeStop()),
//   ComMain (ComMain()), ComUpdate (ComUpdate()), func_020281a8 and func_020281ac (empty functions)

#define COM_WORK ((ComWork *)comWork)

extern u8 comWork[];
extern u8 data_0212c9b8[];
extern u32 data_0212c544;
extern u32 opTitleState;
extern void (*const data_020f258c[])(void);

void ComStart(u8 request);

// func_020280e0 (0x020280e0): the status byte of the communication state.
u32 func_020280e0(void) {
    return COM_WORK->status;
}

// MachiukeStart (0x020280f0): starts the serial, requests code 2 and sets the active flag.
void MachiukeStart(void) {
    MultiSioInit();
    ComStart(2);
    COM_WORK->status = 0;
    COM_WORK->machiukeActive = 1;
}

// MachiukeStop (0x0202811c): restarts the serial with request 0 and clears the status.
void MachiukeStop(void) {
    MultiSioInit();
    ComStart(0);
    COM_WORK->status = 0;
}

// ComMain (0x02028140): ORs opTitleState into data_0212c544, then calls the handler for the current request.
void ComMain(void) {
    data_0212c544 |= opTitleState;
    data_020f258c[COM_WORK->request]();
}

// ComUpdate (0x02028184): sends the data block at data_0212c9b8 and clears its 0x34 bytes.
void ComUpdate(void) {
    MultiSioSendDataSet(data_0212c9b8);
    MemClearFast(data_0212c9b8, 0x34);
}

// Empty functions (dsd names kept, plain symbols).

void func_020281a8(void) {
}

void func_020281ac(void) {
}
