#include "engine/functions.h"
#include "global.h"
#include "types.h"

extern "C" void Vram_DisableBankTail(void);

extern "C" void disableBankForX_(void *bank);
extern u8 data_02129864[];

// Disables the VRAM bank record at data_02129864 (tail call).
ARM void Vram_DisableBankTail(void) {
    disableBankForX_(data_02129864);
}
