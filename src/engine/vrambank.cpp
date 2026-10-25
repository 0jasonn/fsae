#include "engine/functions.h"
#include "global.h"
#include "types.h"
#include "engine/callees.h"

// VRAM bank reset helpers. Each clears one display control bit (main DISPCNT at 0x04000000, sub DISPCNT at
// 0x04001000) and then resets one bank record in the 0x02129864 table through resetBankForX_.

extern "C" void Vram_ResetBankC(void);
extern "C" void Vram_ResetBankD(void);
extern "C" void Vram_ResetSubBankA(void);
extern "C" void Vram_ResetSubBankB(void);

ARM void Vram_ResetMainBankA(void) {
    *(volatile u32 *)0x4000000 &= ~0x40000000;
    resetBankForX_(data_02129872);
}

ARM void Vram_ResetMainBankB(void) {
    *(volatile u32 *)0x4000000 &= ~0x80000000;
    resetBankForX_(data_02129874);
}

ARM void Vram_ResetBankC(void) {
    resetBankForX_(data_0212986c);
}

ARM void Vram_ResetBankD(void) {
    resetBankForX_(data_0212986e);
}

ARM void Vram_ResetSubBankA(void) {
    *(volatile u32 *)0x4001000 &= ~0x40000000;
    resetBankForX_(data_0212987a);
}

ARM void Vram_ResetSubBankB(void) {
    *(volatile u32 *)0x4001000 &= ~0x80000000;
    resetBankForX_(data_0212987c);
}
