// NONMATCHING: 0x370 bytes in ROM, this build is 0x37c (extra loads of the data_0212c4dc/data_0212c5bc
// addresses in cases 0/2, and the callee-saved register assignment differs).
#include "Unknown/C/State_C.hpp"
#include "global.h"

struct Vars_0212c5bc {
    /* 00 */ u16 unk_00;
    /* 02 */ u16 unk_02;
    /* 04 */ u8 unk_04[0xe];
    /* 12 */ u8 unk_12;
};

struct Vars_0212c75c {
    /* 00 */ u16 unk_00;
    /* 02 */ u8 unk_02[0x12];
    /* 14 */ u16 unk_14;
    /* 16 */ u16 unk_16;
    /* 18 */ u16 unk_18;
};

extern Vars_0212c5bc data_0212c5bc;
extern Vars_0212c75c data_0212c75c;
extern u16 data_0212c58c[4];
extern u16 data_0212c584[4];
extern u8 data_0212c4c8;
extern u8 data_0212c5ac;
extern u8 data_0212c4dc;
extern u8 data_0212c4f8;
extern void (*data_0212c564)(void);
extern u16 data_021355a0;
extern const u16 data_020ce4d0[];

extern "C" {
void func_0204625c(int a, int b);
void func_020827a8(int a);
void func_02056f0c(void);
void func_02023b50(void);
void func_0208309c(void);
void func_02026b98(void);
void func_020830ec(void);
void func_02080ed4(void);
void func_0209e26c(void *p, u8 v);
void func_0209eb70(void *p);
void func_0209eb7c(void *p);
void func_02076fe0(int sfx);
void func_0202a60c(void);
void func_0204bb9c(void);
void func_0204bbb8(void);
void func_02080e58(void);
void func_02027dc4(void);
void func_0204a048(void);
void func_02029b38(int a);
void func_02029fe8(int a);
void MIi_CpuClearFast(u32 v, void *dst, u32 size);
Entity *func_02072554(u8 i);
void func_02082ee0(int a);
}

ARM extern "C" void func_02048948(void) {
    u8 *sys;
    int i = 0;
    u16 cnt;
    u8 state;
    sys = func_0208da4c();
    data_0212c58c[3] = i;
    data_0212c58c[2] = i;
    data_0212c58c[1] = i;
    data_0212c58c[0] = i;
    data_0212c584[3] = i;
    data_0212c584[2] = i;
    data_0212c584[1] = i;
    cnt = data_0212c5bc.unk_00;
    state = data_0212c4dc;
    data_0212c584[0] = i;
    data_0212c5bc.unk_00 = cnt + 1;
    switch (state) {
    case 0:
        data_0212c5bc.unk_12 &= 3;
        {
            u16 t = data_0212c5bc.unk_02;
            data_0212c5bc.unk_02 = t - 1;
            if (t == 0) {
                func_0204625c(1, 8);
                func_020827a8(8);
                data_0212c4dc++;
            }
        }
        data_0212c564();
        func_02056f0c();
        func_02023b50();
        func_0208309c();
        func_02026b98();
        func_020830ec();
        func_02080ed4();
        return;
    case 1:
        func_0209e26c(sys + 0x1f8, data_0212c4c8);
        if (data_0212c5ac != 0) {
            return;
        }
        func_0202a60c();
        *(u16 *)0x05000000 = 0;
        data_021355a0 = 0;
        func_0204bb9c();
        func_0204bbb8();
        func_02080e58();
        func_02027dc4();
        func_0204a048();
        MIi_CpuClearFast(0, (void *)0x6001000, 0x800);
        func_02029b38(2);
        func_02029b38(0x15);
        func_02029fe8(0x1b);
        *(u16 *)0x05000000 = 0;
        data_021355a0 = 0;
        data_0212c75c.unk_00 = 0x1240;
        data_0212c75c.unk_14 = data_020ce4d0[0x15];
        data_0212c75c.unk_18 = 0;
        data_0212c75c.unk_16 = data_0212c75c.unk_18;
        func_0208da4c();
        if (func_0208de54() == 0) {
            for (i = 0; i < 2; i++) {
                Entity *e = func_02072554(i);
                e->unk_1c.b0 = 2;
                e->unk_1c.b30 = 0;
                e->unk_30.HALF.HI = i * 0x14 + 0x76;
                e->unk_34.HALF.HI = (i << 4) + 0x98;
                data_0212ceb0[i].unk_0c = 6;
                data_0212ceb0[i].unk_38 = 1;
            }
        } else {
            Entity *e = func_02072554(data_0212c5bc.unk_12);
            e->unk_1c.b0 = 2;
            e->unk_1c.b30 = 0;
            e->unk_30.HALF.HI = 0x80;
            e->unk_34.HALF.HI = 0xa0;
            data_0212ceb0[data_0212c5bc.unk_12].unk_0c = 6;
            data_0212ceb0[data_0212c5bc.unk_12].unk_38 = 1;
        }
        func_0209eb70(sys + 0x1f8);
        func_0209eb7c(sys + 0x1f8);
        data_0212c5bc.unk_02 = 0x1e0;
        data_0212c4dc = data_0212c4dc + 1;
        data_0212c4f8 = 0;
        func_02076fe0(0x800b01a0);
        func_0204625c(0, 8);
        return;
    case 2:
        func_02029b38(2);
        func_02029b38(0x15);
        func_0209e26c(sys + 0x1f8, data_0212c4c8);
        data_0212c564();
        func_020830ec();
        func_02080ed4();
        if (data_0212c5ac == 0) {
            data_0212c5bc.unk_02--;
        }
        if (data_0212c5ac != 0 || data_0212c5bc.unk_02 != 0) {
            return;
        }
        func_0204625c(3, 8);
        data_0212c4dc = data_0212c4dc + 1;
        return;
    case 3:
        if (data_0212c5ac != 0) {
            return;
        }
        func_02076fe0(0x80040000);
        func_0202a60c();
        func_0204bb9c();
        func_0204bbb8();
        func_02082ee0(5);
        return;
    }
}
