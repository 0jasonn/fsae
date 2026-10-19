#include "engine/entity.h"
#include "global.h"

// Functions in this file (address -> name, pending reviewer apply to symbols.txt):
//   Irq_VCountIrq -> Irq_VCountIrq
//   Irq_VCountSetLine0 -> Irq_VCountSetLine0
//   Irq_Bit7Handler -> Irq_Bit7Handler
//   Global_AllocBlock -> Global_AllocBlock
//   Global_FreeBlock -> Global_FreeBlock
//   Global_CopyToVram -> Global_CopyToVram
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
extern void OS_EnableIrqMask(u32 mask);
extern void GX_VBlankIntr(BOOL enable);
extern void GX_SetVCountEqVal(u32 line);
extern void MI_StopDma(u32 dmaNo);
extern void MI_HBlankDmaCopy16(u32 dmaNo, const void *src, void *dst, u32 size);
extern void MIi_CpuCopyFast(const void *src, void *dst, u32 size);
extern void CP_SaveContext(void *context);
extern void CPi_RestoreContext(void *context);
extern void *EL_GetGlobalAdr(u32 offset, u32 size);
extern void func_0208e188(void *block);
extern void func_0208cb74(u16 id);
extern void func_0208cb94(u16 id);
extern void func_0208cbe8(u16 id);
extern void func_0204f694(void);
extern void func_0204f7ac(void);
extern void func_0208d5d4(void);
extern void func_0209aa58(void);
extern void func_02082c64(void);
extern void func_02082aa8(void);
extern void func_02080ca4(void);
extern void func_02029dd8(void);
extern void func_02029eac(void);
extern void func_020857c8(Entity *e);
extern void func_0208ab14(Entity *e);
extern void func_02085f98(Entity *e, u32 sfx);
extern void DeleteEntity(Entity *e);
extern void Irq_VBlankHandler(void);
extern void Irq_VCountIrq(void);
extern void Irq_VCountSetLine0(void);
extern void Irq_Bit7Handler(void);

ARM void Irq_VCountIrq(void) {
    OS_EnableIrqMask(5);
    data_0212c67c.handler = Irq_VCountSetLine0;
}

ARM void Irq_VCountSetLine0(void) {
    OS_EnableIrqMask(5);
    GX_SetVCountEqVal(0);
    data_0212c67c.handler = Irq_VCountIrq;
}

ARM void Irq_Bit7Handler(void) {
    func_0204f7ac();
}

ARM void Global_AllocBlock(void) {
    data_0210389c.block = EL_GetGlobalAdr(0x20000, 0x20);
}

ARM void Global_FreeBlock(void) {
    if (data_0210389c.block == NULL) {
        return;
    }
    func_0208e188(data_0210389c.block);
    data_0210389c.block = NULL;
}

ARM void Global_CopyToVram(u32 dstOffset, u32 srcOffset, u32 size) {
    MIi_CpuCopyFast(data_0210389c.block + srcOffset, (void *)(0x06004000 + dstOffset), size);
}

ARM void Entity_RunAction(Entity *e) {
    if (data_0212c4b8 == 0) {
        data_02103be8[e->action](e);
    }
    func_020857c8(e);
}
