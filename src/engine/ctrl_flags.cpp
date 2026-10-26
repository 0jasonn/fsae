#include "engine/functions.h"
#include "global.h"
#include "types.h"
#include "engine/rect_f.h"

// ctrl_flags: functions Ctrl_updateAc (0x020bb660), Ctrl_tryChange (0x020bb698), Ctrl_updateAd (0x020bb6c8) and
// Ctrl_setCounterA (0x020bb70c), provisional names. The controller record is the one of slider_ctrl.cpp, with the
// pointers at +0x1c, +0x68 and +0x6c and the flag bytes at +0xac and +0xad.

// Controller record of this unit
typedef struct CtrlFlags {
    u8 unk_00[0x1c];
    void *unk_1c;     // 0x1c
    u8 unk_20[6];
    s16 unk_26;       // 0x26
    u8 unk_28[0x34];
    void *unk_5c;     // 0x5c
    void *unk_60;     // 0x60
    u8 unk_64[4];
    void *unk_68;     // 0x68
    void *unk_6c;     // 0x6c
    u8 unk_70[0x2a];
    s16 unk_9a;       // 0x9a
    u8 unk_9c[0x10];
    u8 flagAc;        // 0xac
    u8 flagAd;        // 0xad
} CtrlFlags;

// Record of the pointer at +0x5c (the slider): two halfwords at +0x38 and +0x3a
typedef struct CtrlSlider {
    u8 unk_00[0x38];
    s16 unk_38;       // 0x38
    s16 unk_3a;       // 0x3a
} CtrlSlider;

// Record of the pointer at +0x60: a halfword at +4
typedef struct CtrlRef {
    u8 unk_00[4];
    s16 unk_04;       // 0x04
} CtrlRef;


// Ctrl_updateAc(self) (0x020bb660, provisional name): func_020bb980 with 1 when flagAc is zero (otherwise 0), then
// Menu_AcquirePoolEntry on the pointer at +0x1c with 2 and 0x80; returns flagAc
extern "C" u8 Ctrl_updateAc(CtrlFlags *self);
ARM u8 Ctrl_updateAc(CtrlFlags *self) {
    func_020bb980(self, (self->flagAc == 0) ? 1 : 0);
    Menu_AcquirePoolEntry(self->unk_1c, 2, 0x80);
    return self->flagAc;
}

// Ctrl_tryChange(self, out) (0x020bb698, provisional name): returns 0 when Ctrl_isReady (self, out) reports a change,
// otherwise stores the result of Ctrl_updateAc at out and returns 1
extern "C" s32 Ctrl_tryChange(CtrlFlags *self, u8 *out);
ARM s32 Ctrl_tryChange(CtrlFlags *self, u8 *out) {
    if (Ctrl_isReady(self) != 0) {
        return 0;
    }
    *out = Ctrl_updateAc(self);
    return 1;
}

// Ctrl_updateAd(self) (0x020bb6c8, provisional name): Ctrl_setFlagAndUpdate with 1 when flagAd is zero (otherwise 0),
// the halfword at +0x18 of the pointer at +0x6c set to 10, then Menu_AcquirePoolEntry on the pointer at +0x1c with 8 and 0x80;
// returns flagAd
extern "C" u8 Ctrl_updateAd(CtrlFlags *self);
ARM u8 Ctrl_updateAd(CtrlFlags *self) {
    Ctrl_setFlagAndUpdate((void *)self, (self->flagAd == 0) ? 1 : 0);
    ((s16 *)self->unk_6c)[0x18 / 2] = 10;
    Menu_AcquirePoolEntry(self->unk_1c, 8, 0x80);
    return self->flagAd;
}

// Ctrl_setCounterA(self) (0x020bb70c, provisional name): the halfword at +0x18 of the pointer at +0x68 set to 10, then
// Menu_AcquirePoolEntry on the pointer at +0x1c with 4 and 0x80
extern "C" void Ctrl_setCounterA(CtrlFlags *self);
ARM void Ctrl_setCounterA(CtrlFlags *self) {
    ((s16 *)self->unk_68)[0x18 / 2] = 10;
    Menu_AcquirePoolEntry(self->unk_1c, 4, 0x80);
}

// Ctrl_isReady(self) (0x020bb730, provisional name): 0 when the halfword at +0x26 is in 1..0x95 and the flag is set,
// the halfword at +0x9a equals the one at +4 of the pointer at +0x60 (outside that range) and the two halfwords of the
// slider at +0x5c are equal; otherwise 1
ARM s32 Ctrl_isReady(void *selfObj) {
    CtrlFlags *self = (CtrlFlags *)selfObj;
    s32 result = 1;
    s32 flag = 1;
    s32 inRange = 0;
    s16 pos = self->unk_26;

    if (pos > 0) {
        if (pos < 0x96) {
            inRange = 1;
        }
    }
    if (inRange == 0) {
        if (self->unk_9a == ((CtrlRef *)self->unk_60)->unk_04) {
            flag = 0;
        }
    }
    if (flag == 0) {
        if (((CtrlSlider *)self->unk_5c)->unk_38 == ((CtrlSlider *)self->unk_5c)->unk_3a) {
            result = 0;
        }
    }
    return result;
}
