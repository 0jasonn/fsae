#include "engine/functions.h"
#include "global.h"

extern "C" {
u32 OS_DisableInterrupts(void);
void OS_RestoreInterrupts(u32 saved);
u32 CRYPTOi__r_rand_set_default_init_flag(u32 value);
void SND_InvalidateSeqData(void *obj, void *end);
void SND_InvalidateBankData(void *obj, void *end);
void SND_DestroyBank(void *obj);
void SND_InvalidateWaveData(void *obj, void *end);
void SND_DestroyWaveArc(void *obj);
}

extern "C" u32 SndTable_GetWord14(s32 index);
extern "C" void SndTable_SetWord14(s32 index, u32 value);

// SndBank_Detach: when data is not null, disables interrupts, exchanges the default flag with data, and clears the table
// entry at index when it belongs to obj. Then the flag is restored and the interrupts too.
extern "C" void SndBank_Detach(void *obj, void *data, s32 index);
ARM void SndBank_Detach(void *obj, void *data, s32 index) {
    u32 saved;
    u32 irq;

    if (data == 0) {
        return;
    }
    irq = OS_DisableInterrupts();
    saved = CRYPTOi__r_rand_set_default_init_flag((u32)data);
    if ((u32)obj == SndTable_GetWord14(index)) {
        SndTable_SetWord14(index, 0);
    }
    CRYPTOi__r_rand_set_default_init_flag(saved);
    OS_RestoreInterrupts(irq);
}

// SndBank_ReleaseSeqData: detaches obj, then invalidates its sequence data for size bytes.
extern "C" void SndBank_ReleaseSeqData(void *obj, u32 size, void *data, s32 index);
ARM void SndBank_ReleaseSeqData(void *obj, u32 size, void *data, s32 index) {
    SndBank_Detach(obj, data, index);
    SND_InvalidateSeqData(obj, (u8 *)obj + size);
}

// SndBank_ReleaseBank: detaches obj, invalidates its bank data for size bytes and destroys the bank.
extern "C" void SndBank_ReleaseBank(void *obj, u32 size, void *data, s32 index);
ARM void SndBank_ReleaseBank(void *obj, u32 size, void *data, s32 index) {
    SndBank_Detach(obj, data, index);
    SND_InvalidateBankData(obj, (u8 *)obj + size);
    SND_DestroyBank(obj);
}

// SndBank_ReleaseWave: detaches obj, invalidates its wave data for size bytes and destroys the wave archive.
extern "C" void SndBank_ReleaseWave(void *obj, u32 size, void *data, s32 index);
ARM void SndBank_ReleaseWave(void *obj, u32 size, void *data, s32 index) {
    SndBank_Detach(obj, data, index);
    SND_InvalidateWaveData(obj, (u8 *)obj + size);
    SND_DestroyWaveArc(obj);
}

// SndBank_ReleaseWaveArc: detaches obj and destroys its wave archive (the second argument is not used).
extern "C" void SndBank_ReleaseWaveArc(void *obj, s32 unused, void *data, s32 index);
ARM void SndBank_ReleaseWaveArc(void *obj, s32 unused, void *data, s32 index) {
    SndBank_Detach(obj, data, index);
    SND_DestroyWaveArc(obj);
}
