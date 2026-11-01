#ifndef WIP_B_COMM_H
#define WIP_B_COMM_H

// Communication (com_*, keysync, comerror) functions shared by the B units. Original signatures from the debug build.
#include "engine/functions.h"

void ComStart(u8 request);               // original ComStart(unsigned char)
void ComRequest(u8 request);             // original ComRequest(unsigned char)
void ComFinish(u32 finishArg);           // original ComFinish(unsigned long)
int CommStatusSync(u8 status);           // original CommStatusSync(unsigned char)
void CommErrorCheck(u32 a);              // original CommErrorCheck(unsigned long)
void key_update(u8 playerNo);            // original key_update(unsigned char)
void frame_ack(void);                    // original frame_ack()
void func_0202809c(void);                // dsd name (ComFinish(0)), C++ linkage as in stageseldecls.h
extern "C" int Knife_Comm_WirelessManager_getFrameFlag(void *manager); // dsd name (0x020921b0), nonzero when the manager has finished

#endif
