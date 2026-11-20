#include "engine/functions.h"
#include "global.h"
#include "types.h"
#include "knife/comm/com_sio.h"
#include "knife/comm/com.h"

// Functions in this file (module com, original names from the debug build):
//   ComStart (ComStart(unsigned char)), ComRequest (ComRequest(unsigned char)), ComFinish (ComFinish(unsigned long)),
//   func_0202809c (ComFinish(0), dsd name kept because stageseldecls.h declares it)


void ComRequest(u8 request);

// ComStart (0x02028068): sends the request, then starts the multiplayer serial.
void ComStart(u8 request) {
    ComRequest(request);
    MultiSioStart();
}

// ComRequest (0x02028078): stores the request code and resets the phase and the request state.
void ComRequest(u8 request) {
    comWork.request = request;
    comWork.phase = 0;
    comWork.requestFlag = 1;
    comWork.result = 0;
    comWork.errorTimer = 0;
}

// func_0202809c (0x0202809c): ComFinish with argument 0. C++ linkage, as stageseldecls.h declares it.
void func_0202809c(void) {
    ComFinish(0);
}

// ComFinish (0x020280ac): ends the request and keeps the argument in finishArg.
void ComFinish(u32 finishArg) {
    comWork.request = 0;
    comWork.phase = 0;
    comWork.requestFlag = 0;
    comWork.result = finishArg;
    comWork.errorTimer = 0;
}
