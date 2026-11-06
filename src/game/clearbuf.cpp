#include "engine/functions.h"
#include "global.h"
#include "types.h"

// Functions in this file (provisional names, original functions are ClearWorkBuffer):
//   ClearWorkBuffer -> ClearWorkBuffer

extern u8 data_0213a7a0[]; // work buffer cleared by ClearWorkBuffer

// Clears the 0x2800 bytes of the work buffer (tail call of the clear helper).
void ClearWorkBuffer(void) {
    MemClearFast(data_0213a7a0, 0x2800);
}
