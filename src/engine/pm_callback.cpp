#include "engine/functions.h"
#include "global.h"
#include "types.h"

// Callback block at data_0212b920: a busy flag at +0x30, the callback at +0x34 and its argument at +0x38.
typedef struct PmCallbackBlock {
    u8 unk_00[0x30];
    u32 busy;
    void (*callback)(u32, u32);
    u32 arg;
} PmCallbackBlock;

extern PmCallbackBlock data_0212b920;

extern "C" void PMi_RunCallback(u32 result);

// PMi_RunCallback(result) (0x0201c854): clears the busy flag, then takes the callback (if any), clears it and calls it with
// result and the stored argument.
ARM void PMi_RunCallback(u32 result) {
    void (*callback)(u32, u32);
    u32 arg;

    arg = data_0212b920.arg;
    callback = data_0212b920.callback;
    data_0212b920.busy = 0;
    if (callback == NULL) {
        return;
    }
    data_0212b920.callback = NULL;
    callback(result, arg);
}
