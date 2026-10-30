#include "engine/functions.h"
#include "global.h"
#include "types.h"

// ctrl_init: functions Ctrl_initA (0x020bc0e4) and Ctrl_initB (0x020bc170), provisional names. They differ in the
// clear flag, the final mode and the three data tables.

extern u8 data_02127050[];
extern u8 data_0212706c[];
extern u8 data_02127088[];
extern u8 data_021270a4[];
extern u8 data_021270c8[];
extern u8 data_021270ec[];

extern "C" void func_020c35a4(void *dst, s32 value, s32 size, s32 flag);
extern "C" void func_020c3b94(void *a, s32 b, s32 c, s32 *d);
extern "C" void *Ctrl_findEntryA(void *self, void *id);
extern "C" void *Ctrl_findEntryB(void *self, void *id);
extern "C" void *Ctrl_findEntryC(void *self, void *id);
extern "C" void Slots_ClearThree(s32 *slots);

// Controller record: the argument at +0, the entries found at +4 and +8, the block cleared at +0x2c18
typedef struct CtrlInit {
    void *arg;         // 0x00
    void *entryA;      // 0x04
    void *entryB;      // 0x08
    u8 unk_0c[0x2c18 - 0x0c];
} CtrlInit;

// Ctrl_initA(self, arg) (0x020bc0e4, provisional name): stores arg, clears 0x80 bytes of the block at +0x2c18 (flag 0),
// finds the entries A (+0xc) and B (+0x10) and the record C, clears three slots and calls func_020c3b94 with mode 1
extern "C" void Ctrl_initA(void *selfv, void *arg);
ARM void Ctrl_initA(void *selfv, void *arg) {
    CtrlInit *self = (CtrlInit *)selfv;
    void *record;
    s32 slots[9];

    self->arg = arg;
    func_020c35a4((u8 *)self + 0x2c18, 0, 0x80, 0);
    self->entryA = Ctrl_findEntryA((u8 *)self + 0xc, data_02127050);
    self->entryB = Ctrl_findEntryB((u8 *)self + 0x10, data_0212706c);
    Ctrl_findEntryC(&record, data_02127088);
    Slots_ClearThree(slots);
    func_020c3b94(record, 0, 1, slots);
}

// Ctrl_initB(self, arg) (0x020bc170, provisional name): as Ctrl_initA with clear flag 1, other tables and mode 2
extern "C" void Ctrl_initB(void *selfv, void *arg);
ARM void Ctrl_initB(void *selfv, void *arg) {
    CtrlInit *self = (CtrlInit *)selfv;
    void *record;
    s32 slots[9];

    self->arg = arg;
    func_020c35a4((u8 *)self + 0x2c18, 0, 0x80, 1);
    self->entryA = Ctrl_findEntryA((u8 *)self + 0xc, data_021270a4);
    self->entryB = Ctrl_findEntryB((u8 *)self + 0x10, data_021270c8);
    Ctrl_findEntryC(&record, data_021270ec);
    Slots_ClearThree(slots);
    func_020c3b94(record, 0, 2, slots);
}
