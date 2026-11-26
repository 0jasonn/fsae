#include "engine/functions.h"
#include "global.h"
#include "types.h"
#include "sdk/pxi/pxi_fifo.h"

// PXI FIFO control register (0x04000184) and send register (0x04000188).
typedef struct PxiFifoRegs {
    volatile u16 control;
    u16 pad_02;
    volatile u32 send;
} PxiFifoRegs;

#define REG_PXI_FIFO (*(PxiFifoRegs *)0x4000184)
#define REG_PXI_FIFO_CNT (REG_PXI_FIFO.control)
#define REG_PXI_FIFO_SEND (REG_PXI_FIFO.send)

// One word on the PXI FIFO: a 5-bit tag, an error flag and 26 bits of payload.
typedef union PxiFifoMessage {
    u32 raw;
    struct {
        u32 tag : 5;
        u32 err : 1;
        u32 data : 26;
    } e;
} PxiFifoMessage;

// PXI_IsCallbackReady(tag, proc) (0x0201a1b8): the shared system work (0x02fffc00) keeps one mask of tags with an installed callback per processor, at word 0xe2.
s32 PXI_IsCallbackReady(u32 tag, u32 proc) {
    u32 *sharedWork = (u32 *)0x2fffc00;

    return (sharedWork[proc + 0xe2] & (1 << tag)) ? TRUE : FALSE;
}

// PXI_SendWordByFifo(tag, data, err) (0x0201a1dc): returns 0 when queued, -1 on a FIFO error and -2 when the send FIFO is
// full.
s32 PXI_SendWordByFifo(u32 tag, u32 data, u32 err) {
    PxiFifoMessage message;
    u32 savedIrq;

    message.e.tag = tag;
    message.e.err = err;
    message.e.data = data;
    if (REG_PXI_FIFO_CNT & 0x4000) {
        REG_PXI_FIFO_CNT |= 0xc000;
        return -1;
    }
    savedIrq = OS_DisableInterrupts();
    if (REG_PXI_FIFO_CNT & 2) {
        OS_RestoreInterrupts(savedIrq);
        return -2;
    }
    REG_PXI_FIFO_SEND = message.raw;
    OS_RestoreInterrupts(savedIrq);
    return 0;
}
