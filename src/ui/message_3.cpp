#include "engine/functions.h"
#include "engine/entity.h"
#include "global.h"

// Functions in this file (address -> name, pending reviewer apply to symbols.txt):
//   MessageInitialize -> MessageInitialize
//   TelopInitialize -> TelopInitialize

// Work blocks in the bss, accessed by byte offset
extern u8 telopRequest[];
extern u8 messageRequest[];
extern u8 messageBox[];
extern u8 telopBox[];
extern u8 data_0216efbc[];
extern u8 data_0216efe0[];
extern u8 data_0216eff0[];
extern u8 telopWindowSlots[];
extern u8 data_0216f010[];
extern u8 data_0217d350[];


void MessageInitialize(void) {
    MemClearFast(messageRequest, 0x18);
    MemClearFast(messageBox, 0xe8);
    MemClearFast(data_0216efe0, 0x10);
    MemClearFast(data_0216eff0, 0x10);
    MemClearFast(data_0217d350, 4);
    data_0216efbc[0] = 0;
}

void TelopInitialize(void) {
    MemClearFast(telopRequest, 0x18);
    MemClearFast(telopBox, 0xe8);
    MemClearFast(telopWindowSlots, 0x10);
    MemClearFast(data_0216f010, 0x10);
    data_0216efbc[1] = 0;
}
