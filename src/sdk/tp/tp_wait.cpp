#include "engine/functions.h"
#include "global.h"
#include "types.h"
#include "sdk/tp/tp.h"

// TP_WaitBusy(mask) (0x0201c798): spins until every request in mask has finished.
void TP_WaitBusy(s32 mask) {
    while (data_0212b8e4.busyFlags & mask) {
    }
}

// TP_CheckError(mask) (0x0201c7b0): the error flags of the requests in mask.
s32 TP_CheckError(s32 mask) {
    return data_0212b8e4.errorFlags & mask;
}
