#include "engine/functions.h"
#include "global.h"
#include "types.h"
#include "knife/comm/com_sio.h"
#include "knife/comm/com.h"

// Functions in this file (module com, original names from the debug build):
//   ComStart (ComStart(unsigned char)), ComRequest (ComRequest(unsigned char)), ComFinish (ComFinish(unsigned long)),
//   func_0202809c (ComFinish(0), dsd name kept because stageseldecls.h declares it)

#define COM_WORK ((ComWork *)comWork)

extern u8 comWork[];

void ComFinish(u32 finishArg);
void ComRequest(u8 request);

// ComStart (0x02028068): sends the request, then starts the multiplayer serial.
void ComStart(u8 request) {
    ComRequest(request);
    MultiSioStart();
}

// ComRequest (0x02028078): stores the request code and resets the phase and the request state.
void ComRequest(u8 request) {
    COM_WORK->request = request;
    COM_WORK->phase = 0;
    COM_WORK->requestFlag = 1;
    COM_WORK->finishArg = 0;
    COM_WORK->unk_0c = 0;
}

// func_0202809c (0x0202809c): ComFinish with argument 0. C++ linkage, as stageseldecls.h declares it.
void func_0202809c(void) {
    ComFinish(0);
}

// ComFinish (0x020280ac): ends the request and keeps the argument in finishArg.
void ComFinish(u32 finishArg) {
    COM_WORK->request = 0;
    COM_WORK->phase = 0;
    COM_WORK->requestFlag = 0;
    COM_WORK->finishArg = finishArg;
    COM_WORK->unk_0c = 0;
}
