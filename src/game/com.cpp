#include "engine/functions.h"
#include "global.h"
#include "types.h"
#include "game/com_sio.h"

// Functions in this file (module com, original names from the debug build):
//   ComStart (ComStart(unsigned char)), ComRequest (ComRequest(unsigned char)), ComFinish (ComFinish(unsigned long)),
//   func_0202809c (ComFinish(0), dsd name kept because stageseldecls.h declares it)

// Communication state block at data_0212c9a8.
typedef struct ComWork {
    /* 00 */ u8 request;     // request code, set by ComRequest and ComFinish
    /* 01 */ u8 phase;       // cleared by ComRequest and ComFinish
    /* 02 */ u8 unk_02[2];
    /* 04 */ u32 requestFlag; // 1 after ComRequest, 0 after ComFinish
    /* 08 */ u32 finishArg;   // argument of ComFinish, 0 after ComRequest
    /* 0c */ u16 unk_0c;
} ComWork;

#define COM_WORK ((ComWork *)data_0212c9a8)

extern u8 data_0212c9a8[];

void ComFinish(u32 finishArg);
void ComRequest(u8 request);

// ComStart (0x02028068): sends the request, then starts the multiplayer serial.
ARM void ComStart(u8 request) {
    ComRequest(request);
    MultiSioStart();
}

// ComRequest (0x02028078): stores the request code and resets the phase and the request state.
ARM void ComRequest(u8 request) {
    COM_WORK->request = request;
    COM_WORK->phase = 0;
    COM_WORK->requestFlag = 1;
    COM_WORK->finishArg = 0;
    COM_WORK->unk_0c = 0;
}

// func_0202809c (0x0202809c): ComFinish with argument 0. C++ linkage, as stageseldecls.h declares it.
ARM void func_0202809c(void) {
    ComFinish(0);
}

// ComFinish (0x020280ac): ends the request and keeps the argument in finishArg.
ARM void ComFinish(u32 finishArg) {
    COM_WORK->request = 0;
    COM_WORK->phase = 0;
    COM_WORK->requestFlag = 0;
    COM_WORK->finishArg = finishArg;
    COM_WORK->unk_0c = 0;
}
