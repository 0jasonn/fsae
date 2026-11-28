#include "engine/functions.h"
#include "global.h"
#include "types.h"
#include "sdk/pm/pm.h"

// PMi_RunCallback(result) (0x0201c854): clears the busy flag, then takes the callback (if any), clears it and calls it with
// result and the stored argument.
void PMi_RunCallback(u32 result) {
    PMiCallback callback;
    u32 arg;

    arg = data_0212b920.callbackArg;
    callback = data_0212b920.callback;
    data_0212b920.busy = 0;
    if (callback == NULL) {
        return;
    }
    data_0212b920.callback = NULL;
    callback(result, arg);
}
