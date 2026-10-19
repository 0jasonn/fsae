#include "engine/functions.h"
#include "engine/entity.h"
#include "global.h"

// Functions in this file (address -> name, pending reviewer apply to symbols.txt):
//   MessageInitialize -> MessageInitialize
//   TelopInitialize -> TelopInitialize

// Work blocks in the bss, accessed by byte offset
extern u8 telopRequest[];
extern u8 messageRequest[];
extern u8 data_0217d39c[];
extern u8 telopBox[];
extern u8 data_0216efbc[];
extern u8 data_0216efe0[];
extern u8 data_0216eff0[];
extern u8 telopWindowSlots[];
extern u8 data_0216f010[];
extern u8 data_0217d350[];


ARM void MessageInitialize(void) {
    func_02029a50(messageRequest, 0x18);
    func_02029a50(data_0217d39c, 0xe8);
    func_02029a50(data_0216efe0, 0x10);
    func_02029a50(data_0216eff0, 0x10);
    func_02029a50(data_0217d350, 4);
    data_0216efbc[0] = 0;
}

ARM void TelopInitialize(void) {
    func_02029a50(telopRequest, 0x18);
    func_02029a50(telopBox, 0xe8);
    func_02029a50(telopWindowSlots, 0x10);
    func_02029a50(data_0216f010, 0x10);
    data_0216efbc[1] = 0;
}
