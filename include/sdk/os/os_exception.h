#ifndef SDK_OS_OS_EXCEPTION_H
#define SDK_OS_OS_EXCEPTION_H

// TwlSDK OS exception handling: the handler installed in the exception vector of the shared area (0x02fffd9c) saves
// the context to data_02129bf0 and calls the user handler.
#include "types.h"

// Exception state (data_02129bc0; dsd names +4 data_02129bc4 and +0xc data_02129bcc).
typedef struct OsExceptionState {
    /* 00 */ u32 handler;         // debugger handler found in the vector (0 when outside 0x02600000-0x027fffff);
                                  // OSi_ExceptionHandler calls it first
    /* 04 */ u32 unk_04;          // argument of the user handler at +0xc
    /* 08 */ u32 sharedHandler;   // vector value read by OS_InitException
    /* 0c */ u32 enabled;         // user handler, called with (context, +4); none when 0
} OsExceptionState;

extern OsExceptionState data_02129bc0;
extern u8 data_02129bf0[];        // exception context saved by OSi_SetExContext

extern "C" {
void OS_InitException(void);
// Hand-written ARM.
void OSi_ExceptionHandler(void);
void OSi_GetAndDisplayContext(void);
void OSi_SetExContext(void);
void func_02018e80(void);         // calls the user handler with the protection unit on
}

#endif
