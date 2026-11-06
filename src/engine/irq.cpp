#include "engine/functions.h"
#include "game/time_bonus.h"
#include "global.h"
#include "engine/irq.h"

// Functions in this file (address -> name, pending reviewer apply to symbols.txt):
//   LoadTokiWave -> LoadTokiWave
//   UnlockTokiWave -> UnlockTokiWave
//   Irq_InitVBlank -> Irq_InitVBlank

// Hardware registers (volatile 16-bit I/O)
typedef volatile u16 vu16;
#define REG_IME (*(vu16 *)0x04000208)
#define REG_DISPSTAT (*(vu16 *)0x04000004)
#define REG_DIVCNT (*(vu16 *)0x04000280)

extern IrqState irqState;

extern HBlankDmaState hblankDma;

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
void LoadTokiWave(void) {
    func_0208cb74(tokiWaveLockIds[gameState.unk_48]);
    m4aLockWaveData(tokiWaveLockIds[gameState.unk_48]);
}

void UnlockTokiWave(void) {
    m4aUnlockWaveData(tokiWaveUnlockIds[gameState.unk_48]);
}

void Irq_InitVBlank(void) {
    OS_SetIrqFunction(0x80, Irq_Bit7Handler);
    OS_SetIrqFunction(1, VBlankIntr);
    OS_SetIrqFunction(4, VCountIntr);
    OS_EnableIrqMask(5);
    (void)REG_IME;
    REG_IME = 1;
    REG_DISPSTAT |= 0x20;
    GX_VBlankIntr(1);
}
