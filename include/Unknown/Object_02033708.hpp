#ifndef UNKNOWN_OBJECT_02033708_HPP
#define UNKNOWN_OBJECT_02033708_HPP

#include "Unknown/Player.hpp"

// Event controller fields, see event_02033290.cpp
struct Vars_Event {
    /* 00 */ u8 unk_00[0x7d];
    /* 7d */ u8 unk_7d;
};
#define VE(e) VARS(Vars_Event, e)

struct Vars_Lock {
    /* 00 */ u8 unk_00[0x6e];
    /* 6e */ u16 unk_6e;
    /* 70 */ u8 unk_70[0xc];
    /* 7c */ u16 unk_7c;
    /* 7e */ u8 unk_7e;
};
#define VL(e) VARS(Vars_Lock, e)

struct Vars_02033708 {
    /* 00 */ u8 unk_00[0x70];
    /* 70 */ s16 unk_70;
    /* 72 */ u8 unk_72;
    /* 73 */ u8 unk_73;
    /* 74 */ u8 unk_74;
    /* 75 */ u8 unk_75; // side
    /* 76 */ u8 unk_76;
    /* 77 */ u8 unk_77[5];
    /* 7c */ Entity *unk_7c;
};
#define V(e) VARS(Vars_02033708, e)

extern const EntityFunc data_020d101c[];
extern const s8 data_020d0eba[];
extern const u8 data_020d0ef2[];
extern const u32 data_020cf9b8[];
extern const s8 data_020d0f0a[];
extern const s8 data_020d0ec0[];
extern const u8 data_020d0f02[];
extern s32 data_021348b8[];

extern "C" {
void func_0204be88(Entity *e);
void func_0204fd40(Entity *e);
void func_02050840(Entity *e);
void func_02050390(Entity *e, Entity *other, s32 a, s32 b);
void func_02033e10(Entity *e);
void func_02085d78(Entity *e);
void func_02089524(Entity *e);
void func_020340a8(Entity *e);
void *func_0208da4c(void);
int func_0208de54(void *a);
}

#endif
