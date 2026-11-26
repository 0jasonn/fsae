#include "engine/functions.h"
#include "global.h"
#include "types.h"
#include "sdk/snd/mutex_wrap_api.h"
#include "sdk/snd/snd_command.h"

// Lock and unlock of the global mutex at data_02129d94. Both are tail calls with the mutex as the only argument.

void Mutex_LockGlobal(void) {
    OS_LockMutexFromWToR(&data_02129d94);
}

void Mutex_UnlockGlobal(void) {
    OS_UnlockMutex(&data_02129d94);
}
