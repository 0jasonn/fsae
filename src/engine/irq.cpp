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
extern IrqState irqState;

typedef struct HBlankDmaState {
    u8 enabled; // 0x00
    u8 unk_01[3];
    void *src;  // 0x04
    void *dst;  // 0x08
} HBlankDmaState;
extern HBlankDmaState hblankDma;

typedef struct GlobalBuffer {
    u32 unk_00;
    u8 *block; // 0x04, returned by EL_GetGlobalAdr
} GlobalBuffer;
extern GlobalBuffer globalBuffer;

extern const u16 tokiWaveUnlockIds[];
extern const u16 tokiWaveLockIds[];
extern const EntityFunc entityActionTable[];
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
    func_0208cb74(tokiWaveLockIds[data_0212c7c8.unk_48]);
    m4aLockWaveData(tokiWaveLockIds[data_0212c7c8.unk_48]);
}

ARM void UnlockTokiWave(void) {
    m4aUnlockWaveData(tokiWaveUnlockIds[data_0212c7c8.unk_48]);
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
