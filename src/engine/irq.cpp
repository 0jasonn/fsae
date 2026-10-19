#include "engine/functions.h"
#include "game/state_c.h"
#include "global.h"

// Functions in this file (address -> name, pending reviewer apply to symbols.txt):
//   LoadTokiWave -> LoadTokiWave
//   UnlockTokiWave -> UnlockTokiWave
//   Irq_InitVBlank -> Irq_InitVBlank

// Hardware registers (volatile 16-bit I/O)
typedef volatile u16 vu16;
#define REG_IME (*(vu16 *)0x04000208)
#define REG_DISPSTAT (*(vu16 *)0x04000004)
#define REG_DIVCNT (*(vu16 *)0x04000280)

typedef struct IrqState {
    u8 unk_00[8];
    void (*handler)(void); // 0x08
} IrqState;
extern IrqState data_0212c67c;

typedef struct HBlankDmaState {
    u8 enabled; // 0x00
    u8 unk_01[3];
    void *src;  // 0x04
    void *dst;  // 0x08
} HBlankDmaState;
extern HBlankDmaState data_0212c59c;

typedef struct GlobalBuffer {
    u32 unk_00;
    u8 *block; // 0x04, returned by EL_GetGlobalAdr
} GlobalBuffer;
extern GlobalBuffer data_0210389c;

extern const u16 data_021036b6[];
extern const u16 data_021036c8[];
extern const EntityFunc data_02103be8[];
extern u8 data_0212c4b8;
extern u8 data_0212c4c8;
extern u8 data_0212c4e0;
extern u8 data_021348f4[];
extern u8 data_0213cfa0[];
extern u16 *data_02158fa0;
extern u16 data_0212c594[];
extern u8 data_02fe0000[];

extern void OS_SetIrqFunction(u32 mask, void (*func)(void));

// Track id from the game state
ARM void LoadTokiWave(void) {
    func_0208cb74(data_021036c8[data_0212c7c8.unk_48]);
    m4aLockWaveData(data_021036c8[data_0212c7c8.unk_48]);
}

ARM void UnlockTokiWave(void) {
    m4aUnlockWaveData(data_021036b6[data_0212c7c8.unk_48]);
}

ARM void Irq_InitVBlank(void) {
    OS_SetIrqFunction(0x80, Irq_Bit7Handler);
    OS_SetIrqFunction(1, VBlankIntr);
    OS_SetIrqFunction(4, VCountIntr);
    OS_EnableIrqMask(5);
    (void)REG_IME;
    REG_IME = 1;
    REG_DISPSTAT |= 0x20;
    GX_VBlankIntr(1);
}
