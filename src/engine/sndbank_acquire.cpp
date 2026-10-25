#include "engine/functions.h"
#include "global.h"

extern "C" {
u32 SndTable_GetWord14(s32 index);
void SndTable_SetWord14(s32 index, u32 value);
void *func_020c05dc(void);
void *func_020c1014(s32 index, void *callback, void *data, s32 index2, void *record);
void SndBank_ReleaseSeqData(void *obj, u32 size, void *data, s32 index);
void SndBank_ReleaseBank(void *obj, u32 size, void *data, s32 index);
void SndBank_ReleaseWave(void *obj, u32 size, void *data, s32 index);
}

// The four SndBank_Acquire* functions share one body. They return the table word at index when it is set. Otherwise
// they build the entry with func_020c1014 (the release callback is the argument), and when flag is set they keep the
// result in the table and use the current sound state as data. SndBank_AcquireSeqData and SndBank_AcquireSeqDataB are
// the same code.

// SndBank_AcquireSeqData (SndBank_AcquireSeqData).
extern "C" void *SndBank_AcquireSeqData(s32 index, void *record, s32 flag);
ARM void *SndBank_AcquireSeqData(s32 index, void *record, s32 flag) {
    void *result;
    void *data;

    result = (void *)SndTable_GetWord14(index);
    if (result == 0) {
        if (flag == 0) {
            data = 0;
        } else {
            data = func_020c05dc();
        }
        result = func_020c1014(index, (void *)SndBank_ReleaseSeqData, data, index, record);
        if (flag != 0 && result != 0) {
            SndTable_SetWord14(index, (u32)result);
        }
    }
    return result;
}

// SndBank_AcquireSeqDataB (SndBank_AcquireSeqDataB).
extern "C" void *SndBank_AcquireSeqDataB(s32 index, void *record, s32 flag);
ARM void *SndBank_AcquireSeqDataB(s32 index, void *record, s32 flag) {
    void *result;
    void *data;

    result = (void *)SndTable_GetWord14(index);
    if (result == 0) {
        if (flag == 0) {
            data = 0;
        } else {
            data = func_020c05dc();
        }
        result = func_020c1014(index, (void *)SndBank_ReleaseSeqData, data, index, record);
        if (flag != 0 && result != 0) {
            SndTable_SetWord14(index, (u32)result);
        }
    }
    return result;
}

// SndBank_AcquireBank (SndBank_AcquireBank).
extern "C" void *SndBank_AcquireBank(s32 index, void *record, s32 flag);
ARM void *SndBank_AcquireBank(s32 index, void *record, s32 flag) {
    void *result;
    void *data;

    result = (void *)SndTable_GetWord14(index);
    if (result == 0) {
        if (flag == 0) {
            data = 0;
        } else {
            data = func_020c05dc();
        }
        result = func_020c1014(index, (void *)SndBank_ReleaseBank, data, index, record);
        if (flag != 0 && result != 0) {
            SndTable_SetWord14(index, (u32)result);
        }
    }
    return result;
}

// SndBank_AcquireWave (SndBank_AcquireWave).
extern "C" void *SndBank_AcquireWave(s32 index, void *record, s32 flag);
ARM void *SndBank_AcquireWave(s32 index, void *record, s32 flag) {
    void *result;
    void *data;

    result = (void *)SndTable_GetWord14(index);
    if (result == 0) {
        if (flag == 0) {
            data = 0;
        } else {
            data = func_020c05dc();
        }
        result = func_020c1014(index, (void *)SndBank_ReleaseWave, data, index, record);
        if (flag != 0 && result != 0) {
            SndTable_SetWord14(index, (u32)result);
        }
    }
    return result;
}
