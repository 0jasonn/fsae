#include "engine/functions.h"
#include "global.h"
#include "types.h"
#include "sdk/gx/gx_vramcnt.h"

// Disables the VRAM bank record at data_02129864 (tail call).
void Vram_DisableBankTail(void) {
    disableBankForX_(data_02129864);
}
