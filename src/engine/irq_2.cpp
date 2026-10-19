#include "engine/functions.h"
#include "engine/entity.h"
#include "global.h"

// Functions in this file (address -> name, pending reviewer apply to symbols.txt):
//   VCountIntr -> VCountIntr
//   VCountIntr2 -> VCountIntr2
//   Irq_Bit7Handler -> Irq_Bit7Handler
//   initializeVirtualScreenData -> initializeVirtualScreenData
//   finalizeVirtualScreenData -> finalizeVirtualScreenData
//   refreshVirtualScreenData -> refreshVirtualScreenData
//   Entity_RunAction -> Entity_RunAction

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

ARM void VCountIntr(void) {
    OS_EnableIrqMask(5);
    irqState.handler = VCountIntr2;
}

ARM void VCountIntr2(void) {
    OS_EnableIrqMask(5);
    GX_SetVCountEqVal(0);
    irqState.handler = VCountIntr;
}

ARM void Irq_Bit7Handler(void) {
    MultiSioIntr();
}

ARM void initializeVirtualScreenData(void) {
    globalBuffer.block = (u8 *)EL_GetGlobalAdr(0x20000, 0x20);
}

ARM void finalizeVirtualScreenData(void) {
    if (globalBuffer.block == NULL) {
        return;
    }
    func_0208e188(globalBuffer.block);
    globalBuffer.block = NULL;
}

ARM void refreshVirtualScreenData(u32 dstOffset, u32 srcOffset, u32 size) {
    MIi_CpuCopyFast(globalBuffer.block + srcOffset, (void *)(0x06004000 + dstOffset), size);
}

ARM void Entity_RunAction(Entity *e) {
    if (data_0212c4b8 == 0) {
        entityActionTable[e->action](e);
    }
    func_020857c8(e);
}
